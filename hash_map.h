#ifdef __cplusplus
extern "C" {
#endif

#if !defined(UNDEFINE_HASH_MAP)
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "structures.h"
#include "limited_dynamic_array.h"

/*
 * Default hashing functions.
 * Assign `_internal_variable_hash`.
*/
#define HMAP_INTTYPE(value) value^((value<<(sizeof(value)*4))|(value>>(sizeof(value)*4)))
/* `condition` on `_internal_variable_i` */
#define HMAP_INTTYPE_ARRAY(ptr, continue_condition) 0;for(char *_internal_variable_i = ptr; continue_condition; _internal_variable_i++){_internal_variable_hash ^= (_internal_variable_hash<<(sizeof(*ptr)*4)) + *_internal_variable_i;}
#define HMAP_STRING(str_ptr) HMAP_INTTYPE_ARRAY(str_ptr ,*_internal_variable_i != '\0')

/* Does nothing; Just for signifying return type */
#define HMAP(map) map

#define HMAP_MAKE(map, map_len) {\
  size_t _internal_variable_len = map_len;\
  map = (typeof(map))((uint32_t *)malloc(sizeof(uint32_t) + _internal_variable_len)*sizeof(void*))+1);\
  for(uint32_t _internal_variable_i = 0; _internal_variable_i < _internal_variable_len; _internal_variable_i++){LDARRAY_MAKE(map[_internal_variable_i]);}\
  0[LDARRAY_SIZE(map)] = _internal_variable_len;\
}

#define HMAP_ADD(map, key_hash, key_ptr, value_ptr) {\
  size_t _internal_variable_hash = key_hash;\
  struct _pointer_pair _internal_variable_pair{(void*)key_ptr, (void*)value_ptr};\
  LDARRAY_ADD(map[_internal_variable_hash%0[LDARRAY_SIZE(map)]], _internal_variable_pair);\
}

#define HMAP_GET_INDEX(map, key_hash, key_ptr, var_index) {\
  size_t _internal_variable_hash = key_hash;\
  index_var = _internal_variable_hash%0[LDARRAY_SIZE(array)];\
}

#define HAMP_GET_OFFSETS(map, key_hash, key_ptr, equality_condition, var_offset_1, var_offset_2){\
  uint32_t _internal_variable_index;\
  HMAP_GET_INDEX(map, key_hash, key_ptr, _internal_variable_index);\
  struct _pointer_pair *const _internal_variable_pair = map[_internal_variable_index];\
  struct _pointer_pair *_internal_variable_i;\
  char _internal_variable_bool = 0;\
  for (_internal_variable_i = _internal_variable_pair; _internal_variable_i < LDARRAY_SIZE(_internal_variable_pair) && !(_internal_variable_bool = (equality_condition)); _internal_variable_i++);\
  var_offset_1 = _internal_variable_index;\
  var_offset_2 = _internal_variable_bool? _internal_variable_i-_internal_variable_pair: -1;\
}

#define HAMP_POP(map, key_hash, key_ptr, equality_condition, var_pointer_pair){\
  uint32_t _internal_variable_1, _internal_variable_2;\
  HAMP_GET_OFFSETS(map, key_hash, key_ptr, equality_condition, _internal_variable_1, _internal_variable_2);\
  if (_internal_variable_2 != -1){\
    struct _pointer_pair* _internal_variable_arr = map[_internal_variable_1];\
    const uint32_t _internal_variable_len = *LDARRAY_SIZE(_internal_variable_arr);\
    var_pointer_pair = _internal_variable_arr[_internal_variable_2];\
    for (uint32_t _internal_variable_i = _internal_variable_2+1; _internal_variable_i < _internal_variable_len; _internal_variable_i++)\
      _internal_variable_arr[_internal_variable_i] = _internal_variable_arr[_internal_variable_i-1];\
  } elsevar_pointer_pair = {NULL,NULL};\
}

#define HMAP_FREE(map) free((void *)LDARRAY_SIZE(map))

#else
#undef UNDEFINE_HASH_MAP
#undef HMAP_INTTYPE
#undef HMAP_INTTYPE_ARRAY
#undef HMAP_STRING
#undef HMAP
#undef HMAP_SIZE
#undef HMAP_MAKE
#undef HMAP_ADD
#undef HMAP_RESIZE
#undef HMAP_FREE
#endif

#ifdef __cplusplus
};
#endif

