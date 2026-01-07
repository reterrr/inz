#include "runtime.hpp"

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <new>
#include <vector>

// =============================================================
// Internal object model
// =============================================================

enum class Tag : std::uint8_t
{
    Null,
    Int, // stored as signed i64
    Float, // stored as f64
    Bool,
    Ref, // stores Obj** (pointer to Obj* storage)
    Struct, // fixed-size field vector (Obj*)
    Box, // either Obj* slots OR typed contiguous payload
};

enum class BoxElemKind : std::uint64_t
{
    ObjPtr = 0, // elements are Obj* slots (vector<Obj*> fields)
    I32 = 1,
    I64 = 2,
    F64 = 3,
    Bool = 4, // stored as u8 0/1
};

// IMPORTANT: This is the SAME Obj as forward-declared in runtime.hpp.
struct Obj final
{
    Tag tag{Tag::Null};
    std::uint64_t rc{1};

    union
    {
        std::int64_t i64;
        double f64;
        bool b;
        Obj** slot_ptr; // Ref: points to slot storage (Obj*)
    } as{};

    // Used for Struct fields and for Box in ObjPtr mode.
    // Must remain stable for slot intrinsics (rt_struct_field_slot, rt_box_elem_slot).
    std::vector<Obj*> fields;

    // Typed Box payload (for non-ObjPtr Box).
    void* box_data = nullptr;
    std::uint64_t box_len = 0;
    std::uint64_t box_elem_size = 0;
    std::uint64_t box_elem_align = 0;
    BoxElemKind box_elem_kind = BoxElemKind::ObjPtr;
};

namespace
{
    static Obj* as_obj(void* p) { return reinterpret_cast<Obj*>(p); }
    static void* as_void(Obj* o) { return reinterpret_cast<void*>(o); }

    // Stable dummy slot for error paths (so returning Obj** is always valid)
    static Obj* g_dummy_slot_value = nullptr;

    static Obj* obj_new_null()
    {
        Obj* o = new(std::nothrow) Obj();
        if (!o) std::abort();
        o->tag = Tag::Null;
        return o;
    }

    static Obj* obj_box_int(std::int64_t v)
    {
        Obj* o = obj_new_null();
        o->tag = Tag::Int;
        o->as.i64 = v;
        return o;
    }

    static Obj* obj_box_float(double v)
    {
        Obj* o = obj_new_null();
        o->tag = Tag::Float;
        o->as.f64 = v;
        return o;
    }

    static Obj* obj_box_bool(bool v)
    {
        Obj* o = obj_new_null();
        o->tag = Tag::Bool;
        o->as.b = v;
        return o;
    }

    static Obj* obj_box_ref(Obj** slot_ptr)
    {
        Obj* o = obj_new_null();
        o->tag = Tag::Ref;
        o->as.slot_ptr = slot_ptr;
        return o;
    }

    static Obj* obj_box_struct(std::int64_t field_count)
    {
        if (field_count < 0) field_count = 0;
        Obj* o = obj_new_null();
        o->tag = Tag::Struct;
        o->fields.assign(static_cast<std::size_t>(field_count), nullptr); // fixed-size
        return o;
    }

    static Obj* expect_tag(Obj* o, Tag t)
    {
        return (o && o->tag == t) ? o : nullptr;
    }

    // ---------------------------------------------------------
    // Helpers: numeric coercion
    // ---------------------------------------------------------
    struct Num final
    {
        bool is_float{false};
        std::int64_t i{0};
        double f{0.0};
        bool ok{false};
    };

    static Num to_num(Obj* o)
    {
        Num n{};
        if (!o) return n;

        switch (o->tag)
        {
        case Tag::Int:
            n.is_float = false;
            n.i = o->as.i64;
            n.f = static_cast<double>(o->as.i64);
            n.ok = true;
            return n;

        case Tag::Float:
            n.is_float = true;
            n.f = o->as.f64;
            if (o->as.f64 >= static_cast<double>(std::numeric_limits<std::int64_t>::min()) &&
                o->as.f64 <= static_cast<double>(std::numeric_limits<std::int64_t>::max()))
                n.i = static_cast<std::int64_t>(o->as.f64);
            n.ok = true;
            return n;

        case Tag::Bool:
            n.is_float = false;
            n.i = o->as.b ? 1 : 0;
            n.f = o->as.b ? 1.0 : 0.0;
            n.ok = true;
            return n;

        default:
            return n;
        }
    }

    static void retain_obj(Obj* o)
    {
        if (!o) return;
        ++o->rc;
    }

    static void release_obj(Obj* o)
    {
        if (!o) return;
        if (--o->rc != 0) return;

        if (o->tag == Tag::Struct)
        {
            for (Obj* ch : o->fields)
                release_obj(ch);
            o->fields.clear();
        }
        else if (o->tag == Tag::Box)
        {
            if (o->box_elem_kind == BoxElemKind::ObjPtr)
            {
                for (Obj* ch : o->fields)
                    release_obj(ch);
                o->fields.clear();
            }
            else
            {
                if (o->box_data)
                {
                    ::operator delete(o->box_data, std::align_val_t(o->box_elem_align));
                    o->box_data = nullptr;
                }
            }
        }

        delete o;
    }

    static Obj* num_result(const Num& a, const Num& b, double fval, std::int64_t ival)
    {
        if (a.is_float || b.is_float) return obj_box_float(fval);
        return obj_box_int(ival);
    }

    static bool eq_impl(Obj* a, Obj* b)
    {
        if (a == b) return true;
        if (!a || !b) return false;

        const Num na = to_num(a);
        const Num nb = to_num(b);
        if (na.ok && nb.ok)
        {
            if (na.is_float || nb.is_float) return na.f == nb.f;
            return na.i == nb.i;
        }

        // bring-up: non-numeric compares are pointer-identity only
        return false;
    }

    static bool cmp_num(void* a0, void* b0, int which)
    {
        Obj* a = as_obj(a0);
        Obj* b = as_obj(b0);
        const Num na = to_num(a);
        const Num nb = to_num(b);
        if (!na.ok || !nb.ok) return false;

        const bool use_float = (na.is_float || nb.is_float);
        if (use_float)
        {
            switch (which)
            {
            case 0: return na.f < nb.f;
            case 1: return na.f <= nb.f;
            case 2: return na.f > nb.f;
            case 3: return na.f >= nb.f;
            default: return false;
            }
        }
        else
        {
            switch (which)
            {
            case 0: return na.i < nb.i;
            case 1: return na.i <= nb.i;
            case 2: return na.i > nb.i;
            case 3: return na.i >= nb.i;
            default: return false;
            }
        }
    }

    static std::int64_t unbox_index_i64(Obj* idx)
    {
        const Num n = to_num(idx);
        if (!n.ok) return -1;
        return n.i;
    }

    static void debug_out_line(const char* s)
    {
        std::cerr << s << std::endl;
    }

    static std::size_t box_len_of(Obj* b)
    {
        if (!b || b->tag != Tag::Box) return 0;
        if (b->box_elem_kind == BoxElemKind::ObjPtr) return b->fields.size();
        return static_cast<std::size_t>(b->box_len);
    }

    static std::byte* box_ptr_at(Obj* b, std::size_t i)
    {
        return reinterpret_cast<std::byte*>(b->box_data) + i * static_cast<std::size_t>(b->box_elem_size);
    }
} // namespace

// =============================================================
// extern "C" runtime API
// =============================================================
extern "C" {
// -------------------------
// ARC
// -------------------------
void rt_release(void* obj) { release_obj(as_obj(obj)); }
void rt_retain(void* obj) { retain_obj(as_obj(obj)); }

// -------------------------
// Memory / misc
// -------------------------
void* rt_alloc(long long n)
{
    if (n <= 0) n = 1;
    void* p = std::malloc(static_cast<std::size_t>(n));
    if (!p) std::abort();
    return p;
}

void rt_free(void* p) { std::free(p); }

void rt_print(void* p0)
{
    Obj* o = as_obj(p0);
    if (!o)
    {
        debug_out_line("null");
        return;
    }

    switch (o->tag)
    {
    case Tag::Null:
        debug_out_line("null");
        return;

    case Tag::Int:
        std::cerr << o->as.i64 << std::endl;
        return;

    case Tag::Float:
        std::cerr << o->as.f64 << std::endl;
        return;

    case Tag::Bool:
        debug_out_line(o->as.b ? "true" : "false");
        return;

    case Tag::Ref:
        debug_out_line("<ref>");
        return;

    case Tag::Struct:
        std::cerr << "<struct fields=" << o->fields.size() << ">" << std::endl;
        return;

    case Tag::Box:
        if (o->box_elem_kind == BoxElemKind::ObjPtr)
            std::cerr << "<box(obj*) len=" << o->fields.size() << ">" << std::endl;
        else
            std::cerr << "<box(typed) len=" << static_cast<unsigned long long>(o->box_len) << ">" << std::endl;
        return;

    default:
        debug_out_line("<unknown>");
        return;
    }
}

// -------------------------
// Boxing / unboxing
// -------------------------
 void* rt_int_from_i64(long long v) { return as_void(obj_box_int(static_cast<std::int64_t>(v))); }

void* rt_int_from_u64(unsigned long long v)
{
    // bring-up: store in signed i64 (wrap if above max)
    return as_void(obj_box_int(static_cast<std::int64_t>(v)));
}

#if defined(__SIZEOF_INT128__)
void* rt_int_from_i128(__int128 v) { return rt_int_from_i64(static_cast<long long>(v)); }
void* rt_int_from_u128(unsigned __int128 v) { return rt_int_from_u64(static_cast<unsigned long long>(v)); }
#endif

void* rt_float_from_f32(float v) { return as_void(obj_box_float(static_cast<double>(v))); }
void* rt_float_from_f64(double v) { return as_void(obj_box_float(v)); }

void* rt_box_bool(bool v) { return as_void(obj_box_bool(v)); }

bool rt_unbox_bool(void* p)
{
    Obj* o = as_obj(p);
    if (!o) return false;

    switch (o->tag)
    {
    case Tag::Bool: return o->as.b;
    case Tag::Int: return o->as.i64 != 0;
    case Tag::Float: return o->as.f64 != 0.0;
    default: return false;
    }
}

// -------------------------
// Numeric ops
// -------------------------
void* rt_add(void* a0, void* b0)
{
    const Num na = to_num(as_obj(a0));
    const Num nb = to_num(as_obj(b0));
    if (!na.ok || !nb.ok) return nullptr;
    return as_void(num_result(na, nb, na.f + nb.f, na.i + nb.i));
}

void* rt_sub(void* a0, void* b0)
{
    const Num na = to_num(as_obj(a0));
    const Num nb = to_num(as_obj(b0));
    if (!na.ok || !nb.ok) return nullptr;
    return as_void(num_result(na, nb, na.f - nb.f, na.i - nb.i));
}

void* rt_mul(void* a0, void* b0)
{
    const Num na = to_num(as_obj(a0));
    const Num nb = to_num(as_obj(b0));
    if (!na.ok || !nb.ok) return nullptr;
    return as_void(num_result(na, nb, na.f * nb.f, na.i * nb.i));
}

void* rt_div(void* a0, void* b0)
{
    const Num na = to_num(as_obj(a0));
    const Num nb = to_num(as_obj(b0));
    if (!na.ok || !nb.ok) return nullptr;

    if (!na.is_float && !nb.is_float)
    {
        if (nb.i == 0) return nullptr;
        return as_void(obj_box_int(na.i / nb.i));
    }

    if (nb.f == 0.0) return nullptr;
    return as_void(obj_box_float(na.f / nb.f));
}

void* rt_mod(void* a0, void* b0)
{
    const Num na = to_num(as_obj(a0));
    const Num nb = to_num(as_obj(b0));
    if (!na.ok || !nb.ok) return nullptr;

    if (nb.i == 0) return nullptr;
    return as_void(obj_box_int(na.i % nb.i));
}

void* rt_neg(void* x0)
{
    const Num nx = to_num(as_obj(x0));
    if (!nx.ok) return nullptr;
    return as_void(nx.is_float ? obj_box_float(-nx.f) : obj_box_int(-nx.i));
}

// -------------------------
// Comparisons
// -------------------------
bool rt_eq(void* a0, void* b0) { return eq_impl(as_obj(a0), as_obj(b0)); }
bool rt_ne(void* a0, void* b0) { return !eq_impl(as_obj(a0), as_obj(b0)); }
bool rt_lt(void* a0, void* b0) { return cmp_num(a0, b0, 0); }
bool rt_le(void* a0, void* b0) { return cmp_num(a0, b0, 1); }
bool rt_gt(void* a0, void* b0) { return cmp_num(a0, b0, 2); }
bool rt_ge(void* a0, void* b0) { return cmp_num(a0, b0, 3); }

// -------------------------
// Ref model
// -------------------------
void* rt_ref_from_slot(void* slot_addr)
{
    Obj** slot_ptr = reinterpret_cast<Obj**>(slot_addr);
    return as_void(obj_box_ref(slot_ptr));
}

void rt_ref_store(void* ref_obj0, void* value0)
{
    Obj* r = as_obj(ref_obj0);
    Obj* v = as_obj(value0);
    if (!r || r->tag != Tag::Ref || !r->as.slot_ptr) return;

    Obj* old = *(r->as.slot_ptr);

    retain_obj(v); // retain new
    *(r->as.slot_ptr) = v; // store
    release_obj(old); // release old
}

void* rt_ref_load(void* ref_obj0)
{
    Obj* r = as_obj(ref_obj0);
    if (!r || r->tag != Tag::Ref || !r->as.slot_ptr) return nullptr;

    Obj* v = *(r->as.slot_ptr); // may be nullptr
    retain_obj(v); // IMPORTANT: return owned
    return as_void(v);
}

// -------------------------
// Struct model
// -------------------------
void* rt_struct_new(long long /*struct_id*/, long long field_count)
{
    return as_void(obj_box_struct(static_cast<std::int64_t>(field_count)));
}

void rt_struct_set_field(void* obj0, long long index, void* value0)
{
    Obj* o = as_obj(obj0);
    Obj* v = as_obj(value0);
    o = expect_tag(o, Tag::Struct);
    if (!o) return;
    if (index < 0) return;

    const std::size_t i = static_cast<std::size_t>(index);
    if (i >= o->fields.size()) return; // fixed-size: ignore OOB

    Obj* old = o->fields[i];
    retain_obj(v);
    o->fields[i] = v;
    release_obj(old);
}

void* rt_struct_get_field(void* obj0, long long index)
{
    Obj* o = as_obj(obj0);
    o = expect_tag(o, Tag::Struct);
    if (!o) return nullptr;
    if (index < 0) return nullptr;

    const std::size_t i = static_cast<std::size_t>(index);
    if (i >= o->fields.size()) return nullptr;

    Obj* v = o->fields[i];
    retain_obj(v); // owned return
    return as_void(v);
}

Obj** rt_struct_field_slot(Obj* structObj, std::int64_t fieldIndex)
{
    Obj* o = structObj;
    o = expect_tag(o, Tag::Struct);
    if (!o) return &g_dummy_slot_value;

    if (fieldIndex < 0) return &g_dummy_slot_value;
    const std::size_t i = static_cast<std::size_t>(fieldIndex);
    if (i >= o->fields.size()) return &g_dummy_slot_value;

    return &o->fields[i]; // Obj** (address of cell)
}

// -------------------------
// Box model (typed contiguous payload)
// -------------------------
void* box_new(void* lenObj0,
              unsigned long long elem_kind0,
              unsigned long long elem_size0,
              unsigned long long elem_align0)
{
    const Num n = to_num(as_obj(lenObj0));
    std::int64_t len_i64 = (n.ok ? n.i : 0);
    if (len_i64 < 0) len_i64 = 0;

    const std::size_t len = static_cast<std::size_t>(len_i64);

    Obj* o = obj_new_null();
    o->tag = Tag::Box;

    o->box_elem_kind = static_cast<BoxElemKind>(static_cast<std::uint64_t>(elem_kind0));
    o->box_len = static_cast<std::uint64_t>(len);
    o->box_elem_size = static_cast<std::uint64_t>(elem_size0);
    o->box_elem_align = static_cast<std::uint64_t>(elem_align0);

    // Defensive defaults
    if (o->box_elem_align == 0) o->box_elem_align = alignof(void*);
    if (o->box_elem_size == 0) o->box_elem_size = sizeof(void*);

    if (o->box_elem_kind == BoxElemKind::ObjPtr)
    {
        o->fields.assign(len, nullptr);
        o->box_data = nullptr;
        o->box_len = static_cast<std::uint64_t>(o->fields.size());
        o->box_elem_size = sizeof(void*);
        o->box_elem_align = alignof(void*);
        return as_void(o);
    }

    const std::size_t bytes = len * static_cast<std::size_t>(o->box_elem_size);

    if (bytes == 0)
    {
        o->box_data = nullptr;
        return as_void(o);
    }

    void* mem = ::operator new(bytes, std::align_val_t(o->box_elem_align), std::nothrow);
    if (!mem) std::abort();
    std::memset(mem, 0, bytes);

    o->box_data = mem;
    o->fields.clear();
    return as_void(o);
}

void box_free(void* box0)
{
    // In ARC, freeing is just releasing the box object.
    release_obj(as_obj(box0));
}

void* box_len(void* box0)
{
    Obj* b = as_obj(box0);
    b = expect_tag(b, Tag::Box);
    if (!b) return rt_int_from_u64(0);

    return rt_int_from_u64(static_cast<unsigned long long>(box_len_of(b)));
}

    void* box_get(void* box0, void* idx0)
{
    Obj* b = as_obj(box0);
    b = expect_tag(b, Tag::Box);
    if (!b) return nullptr;

    const std::int64_t idx = unbox_index_i64(as_obj(idx0));
    if (idx < 0) return nullptr;

    const std::size_t i = static_cast<std::size_t>(idx);
    const std::size_t n = box_len_of(b);
    if (i >= n) return nullptr;

    // ObjPtr box: return retained element
    if (b->box_elem_kind == BoxElemKind::ObjPtr)
    {
        Obj* v = b->fields[i];
        retain_obj(v);
        return as_void(v);
    }

    // Typed box: read from payload and BOX into Obj*
    if (!b->box_data) return nullptr;

    switch (b->box_elem_kind)
    {
    case BoxElemKind::I32:
        {
            const auto x = *reinterpret_cast<std::int32_t*>(box_ptr_at(b, i));
            return rt_int_from_i64(static_cast<long long>(x));
        }
    case BoxElemKind::I64:
        {
            const auto x = *reinterpret_cast<std::int64_t*>(box_ptr_at(b, i));
            return rt_int_from_i64(static_cast<long long>(x));
        }
    case BoxElemKind::F64:
        {
            const double x = *reinterpret_cast<double*>(box_ptr_at(b, i));
            return rt_float_from_f64(x);
        }
    case BoxElemKind::Bool:
        {
            const auto x = *reinterpret_cast<std::uint8_t*>(box_ptr_at(b, i)) != 0;
            return rt_box_bool(x);
        }
    default:
        return nullptr;
    }
}


void box_set(void* box0, void* idx0, void* v0)
{
    Obj* b = as_obj(box0);
    b = expect_tag(b, Tag::Box);
    if (!b) return;

    const std::int64_t idx = unbox_index_i64(as_obj(idx0));
    if (idx < 0) return;

    const std::size_t i = static_cast<std::size_t>(idx);
    const std::size_t n = box_len_of(b);
    if (i >= n) return; // fixed-size: ignore OOB

    if (b->box_elem_kind == BoxElemKind::ObjPtr)
    {
        Obj* nv = as_obj(v0);
        Obj* old = b->fields[i];
        retain_obj(nv);
        b->fields[i] = nv;
        release_obj(old);
        return;
    }

    if (!b->box_data) return;

    Obj* v = as_obj(v0);

    switch (b->box_elem_kind)
    {
    case BoxElemKind::I32:
        {
            const Num nv = to_num(v);
            const std::int32_t x = nv.ok ? static_cast<std::int32_t>(nv.i) : 0;
            *reinterpret_cast<std::int32_t*>(box_ptr_at(b, i)) = x;
            return;
        }
    case BoxElemKind::I64:
        {
            const Num nv = to_num(v);
            const std::int64_t x = nv.ok ? static_cast<std::int64_t>(nv.i) : 0;
            *reinterpret_cast<std::int64_t*>(box_ptr_at(b, i)) = x;
            return;
        }
    case BoxElemKind::F64:
        {
            const Num nv = to_num(v);
            const double x = nv.ok ? nv.f : 0.0;
            *reinterpret_cast<double*>(box_ptr_at(b, i)) = x;
            return;
        }
    case BoxElemKind::Bool:
        {
            const bool x = rt_unbox_bool(v0);
            *reinterpret_cast<std::uint8_t*>(box_ptr_at(b, i)) = x ? 1u : 0u;
            return;
        }
    default:
        return;
    }
}

Obj** rt_box_elem_slot(Obj* boxObj, Obj* indexObj)
{
    Obj* b = boxObj;
    b = expect_tag(b, Tag::Box);
    if (!b) return &g_dummy_slot_value;

    // Only ObjPtr boxes can provide a stable Obj** cell.
    if (b->box_elem_kind != BoxElemKind::ObjPtr)
        return &g_dummy_slot_value;

    const std::int64_t idx = unbox_index_i64(indexObj);
    if (idx < 0) return &g_dummy_slot_value;

    const std::size_t i = static_cast<std::size_t>(idx);
    if (i >= b->fields.size()) return &g_dummy_slot_value;

    return &b->fields[i];
}

// -------------------------
// load fn stub
// -------------------------
void s(void* /*arg*/)
{
    // bring-up: no-op
}
} // extern "C"
