#ifdef __cplusplus
extern "C" {
#endif

#if !defined(UNDEFINE_DYNAMIC_ARRAY)
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

/* Does nothing; Just for signifying return type */
#define DARRAY(array) array

#define DARRAY_SIZE(array) ((uint32_t *)array-2)

#define DARRAY_MAKE(array) {\
  array = (typeof(array))((uint32_t *)malloc(2*sizeof(uint32_t) + 3*sizeof(*array))+2);\
  0[DARRAY_SIZE(array)] = 0;\
  1[DARRAY_SIZE(array)] = 3;\
}

#define DARRAY_ADD(array, value) {\
  if (0[DARRAY_SIZE(array)] == 1[DARRAY_SIZE(array)]) {\
    1[DARRAY_SIZE(array)] = (1[DARRAY_SIZE(array)]<<1) | 1;\
    array = (typeof(array))((uint32_t *)realloc((void *)DARRAY_SIZE(array), 2*sizeof(uint32_t) + 1[DARRAY_SIZE(array)]*sizeof(*array)) + 2);\
  }\
  array[0[DARRAY_SIZE(array)]++] = value;\
}

#define DARRAY_RESIZE(array, capacity) {\
  0[DARRAY_SIZE(array)] = 0[DARRAY_SIZE(array)] > capacity ? capacity : 0[DARRAY_SIZE(array)];\
  1[DARRAY_SIZE(array)] = capacity;\
}

#define DARRAY_FREE(array) free((void *)DARRAY_SIZE(array));

#else
#undef UNDEFINE_DYNAMIC_ARRAY
#undef DARRAY
#undef DARRAY_SIZE
#undef DARRAY_MAKE
#undef DARRAY_ADD
#undef DARRAY_RESIZE
#undef DARRAY_FREE
#endif

#ifdef __cplusplus
};
#endif

