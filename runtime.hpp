#pragma once
#include <cstdint>

extern "C" {
struct Obj;

// ------------------------------------------------------------
// Memory / misc
// ------------------------------------------------------------
void* rt_alloc(long long n);
void rt_free(void* p);
void rt_retain(void* obj);
void rt_release(void* obj);
void rt_print(void* p);

// ------------------------------------------------------------
// Boxing / unboxing
// ------------------------------------------------------------
void* rt_int_from_i64(long long v);
void* rt_int_from_u64(unsigned long long v);

#if defined(__SIZEOF_INT128__)
void* rt_int_from_i128(__int128 v);
void* rt_int_from_u128(unsigned __int128 v);
#endif

void* rt_float_from_f32(float v);
void* rt_float_from_f64(double v);

void* rt_box_bool(bool v);
bool rt_unbox_bool(void* p);

// ------------------------------------------------------------
// Numeric ops (Obj*, Obj*) -> Obj*
// ------------------------------------------------------------
void* rt_add(void* a, void* b);
void* rt_sub(void* a, void* b);
void* rt_mul(void* a, void* b);
void* rt_div(void* a, void* b);
void* rt_mod(void* a, void* b);
void* rt_neg(void* x);

// ------------------------------------------------------------
// Comparisons (Obj*, Obj*) -> bool
// ------------------------------------------------------------
bool rt_eq(void* a, void* b);
bool rt_ne(void* a, void* b);
bool rt_lt(void* a, void* b);
bool rt_le(void* a, void* b);
bool rt_gt(void* a, void* b);
bool rt_ge(void* a, void* b);

// ------------------------------------------------------------
// Ref model
// ------------------------------------------------------------
void* rt_ref_from_slot(void* slot_addr); // slot_addr points to Obj* storage
void rt_ref_store(void* ref_obj, void* value);
void* rt_ref_load(void* ref_obj);

// ------------------------------------------------------------
// Struct model
// ------------------------------------------------------------
void* rt_struct_new(long long struct_id, long long field_count);
void rt_struct_set_field(void* obj, long long index, void* value);
void* rt_struct_get_field(void* obj, long long index);

// Return address of a field cell (Obj**), used for &obj.field
Obj** rt_struct_field_slot(Obj* structObj, std::int64_t fieldIndex);

// ------------------------------------------------------------
// Box model
// ABI CHANGE: box_new now receives element kind/size/align.
// elem_kind values must match runtime BoxElemKind below.
//
// elem_kind:
//   0 = ObjPtr  (elements are Obj* slots; supports &arr[i])
//   1 = I32
//   2 = I64
//   3 = F64
//   4 = Bool (stored as u8 0/1)
//
// box_get/box_set always operate in language-level values (Obj* boxed).
// ------------------------------------------------------------
void* box_new(void* lenObj,
              unsigned long long elem_kind,
              unsigned long long elem_size,
              unsigned long long elem_align);

void box_free(void* box);
void* box_len(void* box);
void* box_get(void* box, void* idxObj);
void box_set(void* box, void* idxObj, void* value);

// Return address of an element cell (Obj**), used for &arr[i].
// Only valid for ObjPtr boxes; typed boxes return a dummy slot.
Obj** rt_box_elem_slot(Obj* boxObj, Obj* indexObj);

// ------------------------------------------------------------
// "load fn" stub target
// ------------------------------------------------------------
void s(void* arg);
} // extern "C"
