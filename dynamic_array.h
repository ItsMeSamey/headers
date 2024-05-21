#ifdef __cplusplus // if c++
extern "C" {
#endif // end if c++

#if !defined(UNDEFINE_DYNAMIC_ARRAY)
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#define DARRAY(array) array // does nothing; just for signify return type

#define DARRAY_MAKE(array) {\
  array = (typeof(array))((uint32_t *)malloc(2*sizeof(uint32_t) + 3*sizeof(typeof(*array)))+2);\
  0[DARRAY_SIZE(array)] = 0;\
  1[DARRAY_SIZE(array)] = 0;\
}

#define DARRAY_SIZE(array) ((uint32_t *)array-2)

#define DARRAY_ADD(array, value) {\
  if (0[DARRAY_SIZE(array)] == 1[DARRAY_SIZE(array)]) {\
    1[DARRAY_SIZE(array)] = (1[DARRAY_SIZE(array)]<<1) | 1;\
    array = (typeof(array))((uint32_t *)realloc((void *)DARRAY_SIZE(array), 1[DARRAY_SIZE(array)]*sizeof(typeof(*array)) + 2*sizeof(uint32_t)) + 2);\
  }\
  array[0[DARRAY_SIZE(array)]++] = value;\
}

#define DARRAY_RESIZE(array, capacity) {\
  0[DARRAY_SIZE(array)] = 0[DARRAY_SIZE(array)] > capacity ? capacity : 0[DARRAY_SIZE(array)];\
  1[DARRAY_SIZE(array)] = capacity;\
}

#define DARRAY_FREE(array) free((void *)DARRAY_SIZE(array))

#else
#undef UNDEFINE_DYNAMIC_ARRAY
#undef DYNAMIC_ARRAY_HEADER
#undef DARRAY
#undef DARRAY_MAKE
#undef DARRAY_SIZE
#undef DARRAY_ADD
#undef DARRAY_RESIZE
#undef DARRAY_FREE
#endif // end if UNDEFINE_DYNAMIC_ARRAY

#ifdef __cplusplus // if c++
}; // namespace arg_parser
#endif // end if c++

