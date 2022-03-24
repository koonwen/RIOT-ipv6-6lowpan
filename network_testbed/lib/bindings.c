#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/bigarray.h>

typedef struct dummy
{
    uint64_t first;
    uint8_t second
} dummy_t;

CAMLprim value
caml_get_pkt(value v_bigarray)
{
    CAMLparam1(v_bigarray);
    dummy_t *ptr = (dummy_t *)Caml_ba_data_val(v_bigarray);
    ptr->first = 1;
    ptr->second = 'a';
    CAMLreturn(caml_copy_nativeint(1));
}