#ifdef __cplusplus
extern "C" {
#endif

#if !defined(UNDEFINE_DYNAMIC_ARRAY)
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

/* Does nothing; Just for signifying return type */
#define LDARRAY(array) array

#define LDARRAY_SIZE(array) ((uint32_t *)array-1)

#define LDARRAY_MAKE(array) {\
  array = (typeof(array))((uint32_t *)malloc(sizeof(uint32_t)) +1);\
  0[LDARRAY_SIZE(array)] = 0;\
}

#define LDARRAY_ADD(array, value) {\
  if ((0[LDARRAY_SIZE(array)] & (0[LDARRAY_SIZE(array)]+1)) == 0) {\
    0[LDARRAY_SIZE(array)] = (0[LDARRAY_SIZE(array)]<<1) | 1;\
    array = (typeof(array))((uint32_t *)realloc((void *)LDARRAY_SIZE(array), sizeof(uint32_t) + 1[LDARRAY_SIZE(array)]*sizeof(*array)) + 1);\
  }\
  array[0[LDARRAY_SIZE(array)]++] = value;\
}

#define LDARRAY_REDUCE(array, len) {\
  _internal_variable_len = len;\
  while(_internal_variable_len & _internal_variable_len-1) {_internal_variable_len &= _internal_variable_len-1;}\
  0[LDARRAY_SIZE(array)] = len;\
  array = (typeof(array))((uint32_t *)realloc((void*)LDARRAY_SIZE(array), sizeof(uint32_t) + ((_internal_variable_len<<1)-1)*sizeof(*array)) + 1);\
}

#define LDARRAY_FREE(array) free((void *)LDARRAY_SIZE(array));

#else
#undef UNDEFINE_LIMITED_DYNAMIC_ARRAY
#undef LDARRAY
#undef LDARRAY_SIZE
#undef LDARRAY_MAKE
#undef LDARRAY_ADD
#undef LDARRAY_REDUCE
#undef LDARRAY_FREE
#endif

#ifdef __cplusplus
};
#endif

