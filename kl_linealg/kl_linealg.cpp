// kl_linalg.cpp
#include "../runtime.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <Eigen/Dense>
#include <unsupported/Eigen/SpecialFunctions>

#define KOLKA_EXPORT extern "C"

// runtime.hpp should forward-declare Obj (your runtime.cpp uses it for
// rt_struct_field_slot)
struct Obj;

// -------------------------
// Utilities
// -------------------------
static void fatal(const char* msg)
{
    std::fprintf(stderr, "[kolka::linalg] fatal: %s\n", msg);
    std::abort();
}

static inline Obj* as_obj(void* p) { return reinterpret_cast<Obj*>(p); }
static inline void* as_void(Obj* p) { return reinterpret_cast<void*>(p); }

static inline void arc_retain(void* p)
{
    if (p)
        rt_retain(p);
}

static inline void arc_release(void* p)
{
    if (p)
        rt_release(p);
}

// ARC-safe store into struct field slot (Obj** cell) with
// retain(new)/release(old).
static void arc_store_slot(Obj** slot, void* newV)
{
    if (!slot)
        fatal("arc_store_slot: null slot");

    void* oldV = as_void(*slot);

    if (newV)
        rt_retain(newV);
    *slot = as_obj(newV);
    if (oldV)
        rt_release(oldV);
}

// -------------------------
// Box kind mapping (must match your runtime BoxElemKind enum)
// -------------------------
static constexpr unsigned long long BOXK_OBJ = 0;
static constexpr unsigned long long BOXK_I32 = 1;
static constexpr unsigned long long BOXK_I64 = 2;
static constexpr unsigned long long BOXK_F64 = 3;
static constexpr unsigned long long BOXK_BOOL = 4;

// -------------------------
// Matrix struct layout indices (must match your Kolka struct order)
// struct MatrixX { data: Box::<T>; rows: i64; cols: i64; }
// -------------------------
static constexpr std::int64_t MAT_DATA = 0;
static constexpr std::int64_t MAT_ROWS = 1;
static constexpr std::int64_t MAT_COLS = 2;

// Load Struct Obj* from &mut Matrix (ref object). rt_ref_load returns owned.
static Obj* load_struct_from_ref(void* refObj)
{
    if (!refObj)
        fatal("load_struct_from_ref: null ref");
    void* s0 = rt_ref_load(refObj);
    if (!s0)
        fatal("matrix struct is null (initialize struct before calling backend)");
    return as_obj(s0); // owned
}

static Obj** field_slot(Obj* structObj, std::int64_t idx)
{
    Obj** slot = rt_struct_field_slot(structObj, idx);
    if (!slot)
        fatal("rt_struct_field_slot returned null");
    return slot;
}

static void read_dims(Obj* mat, std::int64_t& outR, std::int64_t& outC)
{
    void* rObj = as_void(*field_slot(mat, MAT_ROWS));
    void* cObj = as_void(*field_slot(mat, MAT_COLS));
    if (!rObj || !cObj)
        fatal("matrix dims not initialized (rows/cols null)");
    outR = (std::int64_t)rt_int_to_i64(rObj);
    outC = (std::int64_t)rt_int_to_i64(cObj);
    if (outR < 0 || outC < 0)
        fatal("matrix dims negative");
}

static void write_dims(Obj* mat, std::int64_t r, std::int64_t c)
{
    void* rObj = rt_int_from_i64((long long)r);
    void* cObj = rt_int_from_i64((long long)c);

    arc_store_slot(field_slot(mat, MAT_ROWS), rObj);
    arc_store_slot(field_slot(mat, MAT_COLS), cObj);

    arc_release(rObj);
    arc_release(cObj);
}

static void* ensure_data_box(Obj* mat, std::int64_t wantR, std::int64_t wantC,
                             unsigned long long wantKind,
                             unsigned long long elemSize,
                             unsigned long long elemAlign)
{
    if (wantR < 0 || wantC < 0)
        fatal("ensure_data_box: negative dims");
    const std::int64_t count = wantR * wantC;
    if (wantR != 0 && count / wantR != wantC)
        fatal("ensure_data_box: overflow rows*cols");

    void* curBox = as_void(*field_slot(mat, MAT_DATA));

    if (curBox)
    {
        const long long curLen = rt_box_len_i64(curBox);
        const unsigned long long curKind = rt_box_elem_kind_u64(curBox);
        if (curLen == (long long)count && curKind == wantKind)
        {
            write_dims(mat, wantR, wantC);
            return curBox; // borrowed from struct
        }
    }

    void* countObj = rt_int_from_i64((long long)count);
    void* newBox = box_new(countObj, wantKind, elemSize, elemAlign);
    arc_release(countObj);

    if (!newBox)
        fatal("box_new returned null");

    // Store new box into struct (retain new / release old)
    arc_store_slot(field_slot(mat, MAT_DATA), newBox);
    write_dims(mat, wantR, wantC);

    // release local (struct now owns one ref)
    arc_release(newBox);

    return as_void(*field_slot(mat, MAT_DATA));
}

// -------------------------
// Eigen Maps (RowMajor so ABI is predictable)
// -------------------------
using MatF64RM =
Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using MatI32RM = Eigen::Matrix<std::int32_t, Eigen::Dynamic, Eigen::Dynamic,
                               Eigen::RowMajor>;

static Eigen::Map<MatF64RM> map_f64(void* box, std::int64_t r, std::int64_t c)
{
    void* p = rt_box_raw_data(box);
    if (!p)
        fatal("map_f64: null raw data (box kind mismatch?)");
    return Eigen::Map<MatF64RM>((double*)p, (Eigen::Index)r, (Eigen::Index)c);
}

static Eigen::Map<const MatF64RM> map_f64_const(void* box, std::int64_t r,
                                                std::int64_t c)
{
    void* p = rt_box_raw_data(box);
    if (!p)
        fatal("map_f64_const: null raw data (box kind mismatch?)");
    return Eigen::Map<const MatF64RM>((const double*)p, (Eigen::Index)r,
                                      (Eigen::Index)c);
}

static Eigen::Map<MatI32RM> map_i32(void* box, std::int64_t r, std::int64_t c)
{
    void* p = rt_box_raw_data(box);
    if (!p)
        fatal("map_i32: null raw data (box kind mismatch?)");
    return Eigen::Map<MatI32RM>((std::int32_t*)p, (Eigen::Index)r,
                                (Eigen::Index)c);
}

static Eigen::Map<const MatI32RM> map_i32_const(void* box, std::int64_t r,
                                                std::int64_t c)
{
    void* p = rt_box_raw_data(box);
    if (!p)
        fatal("map_i32_const: null raw data (box kind mismatch?)");
    return Eigen::Map<const MatI32RM>((const std::int32_t*)p, (Eigen::Index)r,
                                      (Eigen::Index)c);
}

static void get_box_and_dims_i32(Obj* s, void*& box, std::int64_t& r,
                                 std::int64_t& c)
{
    read_dims(s, r, c);
    box = as_void(*field_slot(s, MAT_DATA));
    if (!box)
        fatal("matrix data null");
}

static void get_box_and_dims_f64(Obj* s, void*& box, std::int64_t& r,
                                 std::int64_t& c)
{
    read_dims(s, r, c);
    box = as_void(*field_slot(s, MAT_DATA));
    if (!box)
        fatal("matrix data null");
}

static std::int64_t vec_len_from_dims(std::int64_t r, std::int64_t c)
{
    if (r == 1 && c >= 1)
        return c;
    if (c == 1 && r >= 1)
        return r;
    fatal("expected vector shape (1×n or n×1)");
    return 0;
}

// ============================================================
// MatrixI32 lifecycle
// ============================================================

KOLKA_EXPORT void mat_i32_init(void* out_ref, void* rows_obj, void* cols_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    const std::int64_t r = (std::int64_t)rt_int_to_i64(rows_obj);
    const std::int64_t c = (std::int64_t)rt_int_to_i64(cols_obj);

    void* outBox = ensure_data_box(outS, r, c, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, r, c).setZero();

    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_free(void* out_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);

    arc_store_slot(field_slot(outS, MAT_DATA), nullptr);
    write_dims(outS, 0, 0);

    arc_release(as_void(outS));
}

// ============================================================
// MatrixF64 lifecycle
// ============================================================

KOLKA_EXPORT void mat_f64_init(void* out_ref, void* rows_obj, void* cols_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    const std::int64_t r = (std::int64_t)rt_int_to_i64(rows_obj);
    const std::int64_t c = (std::int64_t)rt_int_to_i64(cols_obj);

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, r, c).setZero();

    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_free(void* out_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);

    arc_store_slot(field_slot(outS, MAT_DATA), nullptr);
    write_dims(outS, 0, 0);

    arc_release(as_void(outS));
}

// ============================================================
// Fill / copy
// ============================================================

KOLKA_EXPORT void mat_i32_fill(void* out_ref, void* v_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);

    void* box = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_i32(outS, box, r, c);

    const std::int32_t v = (std::int32_t)rt_int_to_i64(v_obj);
    map_i32(box, r, c).setConstant(v);

    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_fill(void* out_ref, void* v_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);

    void* box = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(outS, box, r, c);

    const double v = rt_float_to_f64(v_obj);
    map_f64(box, r, c).setConstant(v);

    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_copy(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_i32(aS, aBox, r, c);

    void* outBox = ensure_data_box(outS, r, c, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, r, c) = map_i32_const(aBox, r, c);

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_copy(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, r, c) = map_f64_const(aBox, r, c);

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

// ============================================================
// Element access
// ============================================================

KOLKA_EXPORT void* mat_i32_get(void* a_ref, void* r_obj, void* c_obj)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t rows = 0, cols = 0;
    get_box_and_dims_i32(aS, aBox, rows, cols);

    const std::int64_t r = (std::int64_t)rt_int_to_i64(r_obj);
    const std::int64_t c = (std::int64_t)rt_int_to_i64(c_obj);
    if (r < 0 || c < 0 || r >= rows || c >= cols)
        fatal("mat_i32_get: OOB");

    const std::int32_t v =
        map_i32_const(aBox, rows, cols)((Eigen::Index)r, (Eigen::Index)c);

    arc_release(as_void(aS));
    return rt_int_from_i64((long long)v);
}

KOLKA_EXPORT void mat_i32_set(void* a_ref, void* r_obj, void* c_obj,
                              void* v_obj)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t rows = 0, cols = 0;
    get_box_and_dims_i32(aS, aBox, rows, cols);

    const std::int64_t r = (std::int64_t)rt_int_to_i64(r_obj);
    const std::int64_t c = (std::int64_t)rt_int_to_i64(c_obj);
    if (r < 0 || c < 0 || r >= rows || c >= cols)
        fatal("mat_i32_set: OOB");

    const std::int32_t v = (std::int32_t)rt_int_to_i64(v_obj);
    map_i32(aBox, rows, cols)((Eigen::Index)r, (Eigen::Index)c) = v;

    arc_release(as_void(aS));
}

KOLKA_EXPORT void* mat_f64_get(void* a_ref, void* r_obj, void* c_obj)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t rows = 0, cols = 0;
    get_box_and_dims_f64(aS, aBox, rows, cols);

    const std::int64_t r = (std::int64_t)rt_int_to_i64(r_obj);
    const std::int64_t c = (std::int64_t)rt_int_to_i64(c_obj);
    if (r < 0 || c < 0 || r >= rows || c >= cols)
        fatal("mat_f64_get: OOB");

    const double v =
        map_f64_const(aBox, rows, cols)((Eigen::Index)r, (Eigen::Index)c);

    arc_release(as_void(aS));
    return rt_float_from_f64(v);
}

KOLKA_EXPORT void mat_f64_set(void* a_ref, void* r_obj, void* c_obj,
                              void* v_obj)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t rows = 0, cols = 0;
    get_box_and_dims_f64(aS, aBox, rows, cols);

    const std::int64_t r = (std::int64_t)rt_int_to_i64(r_obj);
    const std::int64_t c = (std::int64_t)rt_int_to_i64(c_obj);
    if (r < 0 || c < 0 || r >= rows || c >= cols)
        fatal("mat_f64_set: OOB");

    const double v = rt_float_to_f64(v_obj);
    map_f64(aBox, rows, cols)((Eigen::Index)r, (Eigen::Index)c) = v;

    arc_release(as_void(aS));
}

// ============================================================
// Basic ops
// ============================================================

KOLKA_EXPORT void mat_i32_add(void* out_ref, void* a_ref, void* b_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    std::int64_t ar = 0, ac = 0, br = 0, bc = 0;
    read_dims(aS, ar, ac);
    read_dims(bS, br, bc);
    if (ar != br || ac != bc)
        fatal("mat_i32_add: shape mismatch");

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    void* bBox = as_void(*field_slot(bS, MAT_DATA));
    if (!aBox || !bBox)
        fatal("mat_i32_add: null data");

    void* outBox = ensure_data_box(outS, ar, ac, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, ar, ac) =
        map_i32_const(aBox, ar, ac) + map_i32_const(bBox, br, bc);

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_add(void* out_ref, void* a_ref, void* b_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    std::int64_t ar = 0, ac = 0, br = 0, bc = 0;
    read_dims(aS, ar, ac);
    read_dims(bS, br, bc);
    if (ar != br || ac != bc)
        fatal("mat_f64_add: shape mismatch");

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    void* bBox = as_void(*field_slot(bS, MAT_DATA));
    if (!aBox || !bBox)
        fatal("mat_f64_add: null data");

    void* outBox = ensure_data_box(outS, ar, ac, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, ar, ac) =
        map_f64_const(aBox, ar, ac) + map_f64_const(bBox, br, bc);

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_sub(void* out_ref, void* a_ref, void* b_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    std::int64_t ar = 0, ac = 0, br = 0, bc = 0;
    read_dims(aS, ar, ac);
    read_dims(bS, br, bc);
    if (ar != br || ac != bc)
        fatal("mat_i32_sub: shape mismatch");

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    void* bBox = as_void(*field_slot(bS, MAT_DATA));
    if (!aBox || !bBox)
        fatal("mat_i32_sub: null data");

    void* outBox = ensure_data_box(outS, ar, ac, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, ar, ac) =
        map_i32_const(aBox, ar, ac) - map_i32_const(bBox, br, bc);

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_sub(void* out_ref, void* a_ref, void* b_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    std::int64_t ar = 0, ac = 0, br = 0, bc = 0;
    read_dims(aS, ar, ac);
    read_dims(bS, br, bc);
    if (ar != br || ac != bc)
        fatal("mat_f64_sub: shape mismatch");

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    void* bBox = as_void(*field_slot(bS, MAT_DATA));
    if (!aBox || !bBox)
        fatal("mat_f64_sub: null data");

    void* outBox = ensure_data_box(outS, ar, ac, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, ar, ac) =
        map_f64_const(aBox, ar, ac) - map_f64_const(bBox, br, bc);

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_transpose(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    std::int64_t r = 0, c = 0;
    read_dims(aS, r, c);

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    if (!aBox)
        fatal("mat_i32_transpose: null data");

    void* outBox = ensure_data_box(outS, c, r, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, c, r) = map_i32_const(aBox, r, c).transpose();

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_transpose(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    std::int64_t r = 0, c = 0;
    read_dims(aS, r, c);

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    if (!aBox)
        fatal("mat_f64_transpose: null data");

    void* outBox = ensure_data_box(outS, c, r, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, c, r) = map_f64_const(aBox, r, c).transpose();

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_scale(void* out_ref, void* a_ref, void* scalar_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    std::int64_t r = 0, c = 0;
    read_dims(aS, r, c);
    const std::int32_t k = (std::int32_t)rt_int_to_i64(scalar_obj);

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    if (!aBox)
        fatal("mat_i32_scale: null data");

    void* outBox = ensure_data_box(outS, r, c, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, r, c) = map_i32_const(aBox, r, c) * k;

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_scale(void* out_ref, void* a_ref, void* scalar_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    std::int64_t r = 0, c = 0;
    read_dims(aS, r, c);
    const double k = rt_float_to_f64(scalar_obj);

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    if (!aBox)
        fatal("mat_f64_scale: null data");

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, r, c) = map_f64_const(aBox, r, c) * k;

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_mul(void* out_ref, void* a_ref, void* b_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    std::int64_t ar = 0, ac = 0, br = 0, bc = 0;
    read_dims(aS, ar, ac);
    read_dims(bS, br, bc);
    if (ac != br)
        fatal("mat_i32_mul: inner dims mismatch");

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    void* bBox = as_void(*field_slot(bS, MAT_DATA));
    if (!aBox || !bBox)
        fatal("mat_i32_mul: null data");

    void* outBox = ensure_data_box(outS, ar, bc, BOXK_I32, 4ULL, 4ULL);

    auto Out = map_i32(outBox, ar, bc);
    auto A = map_i32_const(aBox, ar, ac);
    auto B = map_i32_const(bBox, br, bc);
    Out.noalias() = A * B;

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_mul(void* out_ref, void* a_ref, void* b_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    std::int64_t ar = 0, ac = 0, br = 0, bc = 0;
    read_dims(aS, ar, ac);
    read_dims(bS, br, bc);
    if (ac != br)
        fatal("mat_f64_mul: inner dims mismatch");

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    void* bBox = as_void(*field_slot(bS, MAT_DATA));
    if (!aBox || !bBox)
        fatal("mat_f64_mul: null data");

    void* outBox = ensure_data_box(outS, ar, bc, BOXK_F64, 8ULL, 8ULL);

    auto Out = map_f64(outBox, ar, bc);
    auto A = map_f64_const(aBox, ar, ac);
    auto B = map_f64_const(bBox, br, bc);
    Out.noalias() = A * B;

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

// out = alpha*(a*b) + beta*out
KOLKA_EXPORT void mat_f64_gemm(void* out_ref, void* a_ref, void* b_ref,
                               void* alpha_obj, void* beta_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    std::int64_t ar = 0, ac = 0, br = 0, bc = 0;
    read_dims(aS, ar, ac);
    read_dims(bS, br, bc);
    if (ac != br)
        fatal("mat_f64_gemm: inner dims mismatch");

    const double alpha = rt_float_to_f64(alpha_obj);
    const double beta = rt_float_to_f64(beta_obj);

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    void* bBox = as_void(*field_slot(bS, MAT_DATA));
    if (!aBox || !bBox)
        fatal("mat_f64_gemm: null data");

    void* outBox = ensure_data_box(outS, ar, bc, BOXK_F64, 8ULL, 8ULL);

    auto A = map_f64_const(aBox, ar, ac);
    auto B = map_f64_const(bBox, br, bc);
    auto Out = map_f64(outBox, ar, bc);

    // avoid alias issues: compute product into temp
    MatF64RM prod = (A * B);
    Out = (alpha * prod) + (beta * Out);

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

// ============================================================
// Extended: structured constructors
// ============================================================

KOLKA_EXPORT void mat_i32_identity(void* out_ref, void* n_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    const std::int64_t n = (std::int64_t)rt_int_to_i64(n_obj);
    if (n < 0)
        fatal("mat_i32_identity: n < 0");

    void* outBox = ensure_data_box(outS, n, n, BOXK_I32, 4ULL, 4ULL);
    auto Out = map_i32(outBox, n, n);
    Out.setZero();
    Out.diagonal().setOnes();

    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_identity(void* out_ref, void* n_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    const std::int64_t n = (std::int64_t)rt_int_to_i64(n_obj);
    if (n < 0)
        fatal("mat_f64_identity: n < 0");

    void* outBox = ensure_data_box(outS, n, n, BOXK_F64, 8ULL, 8ULL);
    auto Out = map_f64(outBox, n, n);
    Out.setZero();
    Out.diagonal().setOnes();

    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_diag_extract(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    std::int64_t r = 0, c = 0;
    read_dims(aS, r, c);
    const std::int64_t k = (r < c) ? r : c;

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    if (!aBox)
        fatal("mat_i32_diag_extract: null data");

    void* outBox = ensure_data_box(outS, k, 1, BOXK_I32, 4ULL, 4ULL);
    auto Out = map_i32(outBox, k, 1);
    Out.col(0) = map_i32_const(aBox, r, c).diagonal();

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_diag_extract(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    std::int64_t r = 0, c = 0;
    read_dims(aS, r, c);
    const std::int64_t k = (r < c) ? r : c;

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    if (!aBox)
        fatal("mat_f64_diag_extract: null data");

    void* outBox = ensure_data_box(outS, k, 1, BOXK_F64, 8ULL, 8ULL);
    auto Out = map_f64(outBox, k, 1);
    Out.col(0) = map_f64_const(aBox, r, c).diagonal();

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_diag_from_vec(void* out_ref, void* v_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* vS = load_struct_from_ref(v_ref);

    std::int64_t vr = 0, vc = 0;
    read_dims(vS, vr, vc);
    const std::int64_t k = vec_len_from_dims(vr, vc);

    void* vBox = as_void(*field_slot(vS, MAT_DATA));
    if (!vBox)
        fatal("mat_i32_diag_from_vec: null data");

    void* outBox = ensure_data_box(outS, k, k, BOXK_I32, 4ULL, 4ULL);
    auto Out = map_i32(outBox, k, k);
    Out.setZero();

    // map v as vector
    const std::int32_t* vp = (const std::int32_t*)rt_box_raw_data(vBox);
    if (!vp)
        fatal("mat_i32_diag_from_vec: null raw");
    Eigen::Map<const Eigen::Matrix<std::int32_t, Eigen::Dynamic, 1>> V(
        vp, (Eigen::Index)k);
    Out.diagonal() = V;

    arc_release(as_void(vS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_diag_from_vec(void* out_ref, void* v_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* vS = load_struct_from_ref(v_ref);

    std::int64_t vr = 0, vc = 0;
    read_dims(vS, vr, vc);
    const std::int64_t k = vec_len_from_dims(vr, vc);

    void* vBox = as_void(*field_slot(vS, MAT_DATA));
    if (!vBox)
        fatal("mat_f64_diag_from_vec: null data");

    void* outBox = ensure_data_box(outS, k, k, BOXK_F64, 8ULL, 8ULL);
    auto Out = map_f64(outBox, k, k);
    Out.setZero();

    const double* vp = (const double*)rt_box_raw_data(vBox);
    if (!vp)
        fatal("mat_f64_diag_from_vec: null raw");
    Eigen::Map<const Eigen::VectorXd> V(vp, (Eigen::Index)k);
    Out.diagonal() = V;

    arc_release(as_void(vS));
    arc_release(as_void(outS));
}

// ============================================================
// Extended: elementwise unary
// ============================================================

KOLKA_EXPORT void mat_i32_neg(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_i32(aS, aBox, r, c);

    void* outBox = ensure_data_box(outS, r, c, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, r, c) = -map_i32_const(aBox, r, c);

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_neg(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, r, c) = -map_f64_const(aBox, r, c);

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_abs(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_i32(aS, aBox, r, c);

    void* outBox = ensure_data_box(outS, r, c, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, r, c) = map_i32_const(aBox, r, c).cwiseAbs();

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_abs(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, r, c) = map_f64_const(aBox, r, c).cwiseAbs();

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

// ============================================================
// Extended: elementwise binary / scalar
// ============================================================

KOLKA_EXPORT void mat_i32_hadamard(void* out_ref, void* a_ref, void* b_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    std::int64_t ar = 0, ac = 0, br = 0, bc = 0;
    read_dims(aS, ar, ac);
    read_dims(bS, br, bc);
    if (ar != br || ac != bc)
        fatal("mat_i32_hadamard: shape mismatch");

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    void* bBox = as_void(*field_slot(bS, MAT_DATA));
    if (!aBox || !bBox)
        fatal("mat_i32_hadamard: null data");

    void* outBox = ensure_data_box(outS, ar, ac, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, ar, ac).array() =
        map_i32_const(aBox, ar, ac).array() * map_i32_const(bBox, br, bc).array();

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_hadamard(void* out_ref, void* a_ref, void* b_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    std::int64_t ar = 0, ac = 0, br = 0, bc = 0;
    read_dims(aS, ar, ac);
    read_dims(bS, br, bc);
    if (ar != br || ac != bc)
        fatal("mat_f64_hadamard: shape mismatch");

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    void* bBox = as_void(*field_slot(bS, MAT_DATA));
    if (!aBox || !bBox)
        fatal("mat_f64_hadamard: null data");

    void* outBox = ensure_data_box(outS, ar, ac, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, ar, ac).array() =
        map_f64_const(aBox, ar, ac).array() * map_f64_const(bBox, br, bc).array();

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_hadamard_div(void* out_ref, void* a_ref,
                                       void* b_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    std::int64_t ar = 0, ac = 0, br = 0, bc = 0;
    read_dims(aS, ar, ac);
    read_dims(bS, br, bc);
    if (ar != br || ac != bc)
        fatal("mat_f64_hadamard_div: shape mismatch");

    void* aBox = as_void(*field_slot(aS, MAT_DATA));
    void* bBox = as_void(*field_slot(bS, MAT_DATA));
    if (!aBox || !bBox)
        fatal("mat_f64_hadamard_div: null data");

    void* outBox = ensure_data_box(outS, ar, ac, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, ar, ac).array() =
        map_f64_const(aBox, ar, ac).array() / map_f64_const(bBox, br, bc).array();

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_add_scalar(void* out_ref, void* a_ref, void* k_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_i32(aS, aBox, r, c);
    const std::int32_t k = (std::int32_t)rt_int_to_i64(k_obj);

    void* outBox = ensure_data_box(outS, r, c, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, r, c) = map_i32_const(aBox, r, c).array() + k;

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_add_scalar(void* out_ref, void* a_ref, void* k_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);
    const double k = rt_float_to_f64(k_obj);

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, r, c) = map_f64_const(aBox, r, c).array() + k;

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_i32_sub_scalar(void* out_ref, void* a_ref, void* k_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_i32(aS, aBox, r, c);
    const std::int32_t k = (std::int32_t)rt_int_to_i64(k_obj);

    void* outBox = ensure_data_box(outS, r, c, BOXK_I32, 4ULL, 4ULL);
    map_i32(outBox, r, c) = map_i32_const(aBox, r, c).array() - k;

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_sub_scalar(void* out_ref, void* a_ref, void* k_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);
    const double k = rt_float_to_f64(k_obj);

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, r, c) = map_f64_const(aBox, r, c).array() - k;

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_div_scalar(void* out_ref, void* a_ref, void* k_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);
    const double k = rt_float_to_f64(k_obj);
    if (k == 0.0)
        fatal("mat_f64_div_scalar: division by zero");

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);
    map_f64(outBox, r, c) = map_f64_const(aBox, r, c) * (1.0 / k);

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

// ============================================================
// Extended: elementwise f64 math
// ============================================================


#define F64_UNARY_OBJ(name, EXPR)                  \
KOLKA_EXPORT void* name(void* a_obj) {           \
const double a = rt_float_to_f64(a_obj);       \
const double r = (EXPR);                       \
return rt_float_from_f64(r);                   \
}

F64_UNARY_OBJ(f64_sin,   std::sin(a))
F64_UNARY_OBJ(f64_cos,   std::cos(a))
F64_UNARY_OBJ(f64_tan,   std::tan(a))

F64_UNARY_OBJ(f64_asin,  std::asin(a))
F64_UNARY_OBJ(f64_acos,  std::acos(a))
F64_UNARY_OBJ(f64_atan,  std::atan(a))

F64_UNARY_OBJ(f64_sinh,  std::sinh(a))
F64_UNARY_OBJ(f64_cosh,  std::cosh(a))
F64_UNARY_OBJ(f64_tanh,  std::tanh(a))

F64_UNARY_OBJ(f64_exp,   std::exp(a))
F64_UNARY_OBJ(f64_log,   std::log(a))
F64_UNARY_OBJ(f64_log10, std::log10(a))
F64_UNARY_OBJ(f64_sqrt,  std::sqrt(a))

F64_UNARY_OBJ(f64_floor, std::floor(a))
F64_UNARY_OBJ(f64_ceil,  std::ceil(a))
F64_UNARY_OBJ(f64_round, std::round(a))

#undef F64_UNARY_OBJ

KOLKA_EXPORT void mat_f64_pow_scalar(void* out_ref, void* a_ref, void* p_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);
    const double p = rt_float_to_f64(p_obj);

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);
    auto Out = map_f64(outBox, r, c);
    auto A = map_f64_const(aBox, r, c);

    Out.array() = A.array().unaryExpr([p](double x) { return std::pow(x, p); });

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_clamp(void* out_ref, void* a_ref, void* lo_obj,
                                void* hi_obj)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);
    const double lo = rt_float_to_f64(lo_obj);
    const double hi = rt_float_to_f64(hi_obj);
    if (!(lo <= hi))
        fatal("mat_f64_clamp: lo > hi");

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);
    auto Out = map_f64(outBox, r, c);
    auto A = map_f64_const(aBox, r, c);

    Out.array() = A.array().max(lo).min(hi);

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

// ============================================================
// Reductions (return scalars as boxed objects)
// ============================================================

KOLKA_EXPORT void* mat_i32_sum(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_i32(aS, aBox, r, c);

    long long s =
        (long long)map_i32_const(aBox, r, c).template cast<long long>().sum();

    arc_release(as_void(aS));
    return rt_int_from_i64(s);
}

KOLKA_EXPORT void* mat_f64_sum(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    double s = map_f64_const(aBox, r, c).sum();

    arc_release(as_void(aS));
    return rt_float_from_f64(s);
}

KOLKA_EXPORT void* mat_f64_mean(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    double m = map_f64_const(aBox, r, c).mean();

    arc_release(as_void(aS));
    return rt_float_from_f64(m);
}

KOLKA_EXPORT void* mat_i32_min(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_i32(aS, aBox, r, c);

    std::int32_t v = map_i32_const(aBox, r, c).minCoeff();

    arc_release(as_void(aS));
    return rt_int_from_i64((long long)v);
}

KOLKA_EXPORT void* mat_i32_max(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_i32(aS, aBox, r, c);

    std::int32_t v = map_i32_const(aBox, r, c).maxCoeff();

    arc_release(as_void(aS));
    return rt_int_from_i64((long long)v);
}

KOLKA_EXPORT void* mat_f64_min(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    double v = map_f64_const(aBox, r, c).minCoeff();

    arc_release(as_void(aS));
    return rt_float_from_f64(v);
}

KOLKA_EXPORT void* mat_f64_max(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    double v = map_f64_const(aBox, r, c).maxCoeff();

    arc_release(as_void(aS));
    return rt_float_from_f64(v);
}

KOLKA_EXPORT void* mat_i32_trace(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_i32(aS, aBox, r, c);

    const std::int64_t k = (r < c) ? r : c;
    long long t = (long long)map_i32_const(aBox, r, c)
                             .diagonal()
                             .head((Eigen::Index)k)
                             .template cast<long long>()
                             .sum();

    arc_release(as_void(aS));
    return rt_int_from_i64(t);
}

KOLKA_EXPORT void* mat_f64_trace(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    const std::int64_t k = (r < c) ? r : c;
    double t = map_f64_const(aBox, r, c).diagonal().head((Eigen::Index)k).sum();

    arc_release(as_void(aS));
    return rt_float_from_f64(t);
}

KOLKA_EXPORT void* mat_f64_det(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);
    if (r != c)
        fatal("mat_f64_det: not square");

    double d = map_f64_const(aBox, r, c).determinant();

    arc_release(as_void(aS));
    return rt_float_from_f64(d);
}

KOLKA_EXPORT void* mat_f64_norm_fro(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    double n = map_f64_const(aBox, r, c).norm();

    arc_release(as_void(aS));
    return rt_float_from_f64(n);
}

KOLKA_EXPORT void* mat_f64_norm1(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    auto A = map_f64_const(aBox, r, c);
    double n1 = A.cwiseAbs().colwise().sum().maxCoeff();

    arc_release(as_void(aS));
    return rt_float_from_f64(n1);
}

KOLKA_EXPORT void* mat_f64_norm_inf(void* a_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);

    auto A = map_f64_const(aBox, r, c);
    double ni = A.cwiseAbs().rowwise().sum().maxCoeff();

    arc_release(as_void(aS));
    return rt_float_from_f64(ni);
}

KOLKA_EXPORT void* mat_f64_dot(void* a_ref, void* b_ref)
{
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    void* aBox = nullptr;
    std::int64_t ar = 0, ac = 0;
    void* bBox = nullptr;
    std::int64_t br = 0, bc = 0;
    get_box_and_dims_f64(aS, aBox, ar, ac);
    get_box_and_dims_f64(bS, bBox, br, bc);

    const std::int64_t nA = vec_len_from_dims(ar, ac);
    const std::int64_t nB = vec_len_from_dims(br, bc);
    if (nA != nB)
        fatal("mat_f64_dot: length mismatch");

    const double* ap = (const double*)rt_box_raw_data(aBox);
    const double* bp = (const double*)rt_box_raw_data(bBox);
    if (!ap || !bp)
        fatal("mat_f64_dot: null raw data");

    Eigen::Map<const Eigen::VectorXd> A(ap, (Eigen::Index)nA);
    Eigen::Map<const Eigen::VectorXd> B(bp, (Eigen::Index)nB);
    double d = A.dot(B);

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    return rt_float_from_f64(d);
}

// ============================================================
// Linear algebra (f64): inv / solve
// ============================================================

KOLKA_EXPORT void mat_f64_inv(void* out_ref, void* a_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);

    void* aBox = nullptr;
    std::int64_t r = 0, c = 0;
    get_box_and_dims_f64(aS, aBox, r, c);
    if (r != c)
        fatal("mat_f64_inv: not square");

    void* outBox = ensure_data_box(outS, r, c, BOXK_F64, 8ULL, 8ULL);

    MatF64RM A = map_f64_const(aBox, r, c); // copy to avoid alias issues
    Eigen::FullPivLU<MatF64RM> lu(A);
    if (!lu.isInvertible())
        fatal("mat_f64_inv: matrix not invertible");

    MatF64RM X = lu.inverse();
    map_f64(outBox, r, c) = X;

    arc_release(as_void(aS));
    arc_release(as_void(outS));
}

KOLKA_EXPORT void mat_f64_solve(void* out_ref, void* a_ref, void* b_ref)
{
    Obj* outS = load_struct_from_ref(out_ref);
    Obj* aS = load_struct_from_ref(a_ref);
    Obj* bS = load_struct_from_ref(b_ref);

    void* aBox = nullptr;
    std::int64_t ar = 0, ac = 0;
    void* bBox = nullptr;
    std::int64_t br = 0, bc = 0;
    get_box_and_dims_f64(aS, aBox, ar, ac);
    get_box_and_dims_f64(bS, bBox, br, bc);

    if (ar != ac)
        fatal("mat_f64_solve: A not square");
    if (br != ar)
        fatal("mat_f64_solve: row mismatch (B.rows must equal A.rows)");

    void* outBox = ensure_data_box(outS, ac, bc, BOXK_F64, 8ULL, 8ULL);

    MatF64RM A = map_f64_const(aBox, ar, ac); // copy for stability/aliasing
    MatF64RM B = map_f64_const(bBox, br, bc); // copy

    Eigen::FullPivLU<MatF64RM> lu(A);
    if (!lu.isInvertible())
        fatal("mat_f64_solve: A not invertible");

    MatF64RM X = lu.solve(B);
    map_f64(outBox, ac, bc) = X;

    arc_release(as_void(bS));
    arc_release(as_void(aS));
    arc_release(as_void(outS));
}
