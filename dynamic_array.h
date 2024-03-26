#ifdef __cplusplus // if c++
extern "C" {
#endif // end if c++

#ifndef UNDEFINE_DYNAMIC_ARRAY
#ifndef DYNAMIC_ARRAY_HEADER
#define DYNAMIC_ARRAY_HEADER

#include <stdlib.h>

#define __DARRAY(array) array // does nothing; just for signify return type

#define DARRAY_MAKE(type, array) { \
  size_t*__name = (size_t *)malloc(3*sizeof(type) + 2*sizeof(size_t)); \
  __name[0] = 0; \
  __name[1] = 3; \
  array = (type *)(__name+2); \
}

#define DARRAY_SIZE(array) ((size_t *)array-2)

#define DARRAY_ADD(type, array, value) { \
  size_t* __size = DARRAY_SIZE(array); \
  if (__size[0] == __size[1]) { \
    __size[1] = (__size[1]<<1) + 1; \
    array = (type *)((size_t *)realloc((void *)__size, __size[1]*sizeof(type) + 2*sizeof(size_t)) + 2); \
  } \
  array[__size[0]++] = value; \
}

#define DARRAY_RESIZE(type, array, capacity) { \
  size_t* __size = DARRAY_SIZE(array); \
  __size[0] = __size[0] > capacity ? capacity : __size[0]; \
  __size[1] = capacity; \
}

#define DARRAY_FREE(array) free((void *)DARRAY_SIZE(array))


#endif // end if DYNAMIC_ARRAY_H
#endif // end if UNDEFINE_DYNAMIC_ARRAY

#ifdef UNDEFINE_DYNAMIC_ARRAY
#undef UNDEFINE_DYNAMIC_ARRAY
#undef DYNAMIC_ARRAY_HEADER
#undef __DARRAY
#undef DARRAY_MAKE
#undef DARRAY_SIZE
#undef DARRAY_ADD
#undef DARRAY_RESIZE
#undef DARRAY_FREE
#endif 

#ifdef __cplusplus // if c++
}; // namespace arg_parser
#endif // end if c++

