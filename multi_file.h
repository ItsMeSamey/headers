#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#ifdef __cplusplus // if c++
extern "C" {
#endif // end if c++

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "structures.h"
#include "dynamic_array.h"

/*
 * WARN: use `DARRAY_FREE(array);`
*/
#define MULTI_FILE_MAKE(array) DARRAY_MAKE(struct __pointer_pair, array);\

#define  MULTI_FILE_ADD(array, value, len){\
  assert(array != NULL || !"multi_file_read: invalid array");\
  assert(value != NULL || !"multi_file_read: invalid value");\
  struct __pointer_pair pair{(void *)len, (void *) value};\
  DARRAY_ADD(struct __pointer_pair, array, pair)\
}

#define MULTI_FILE_WRITE(array, file){\
  assert(array != NULL || !"multi_file_read: invalid array");\
  assert(file != NULL || !"multi_file_read: invalid file");\
  size_t *size = DARRAY_SIZE(array);\
  fwrite(size, sizeof(size_t), 1, file);\
  const size_t len = *size;\
  for (size_t i = 0, offset = 0; i < len; i++){\
    struct __pointer_pair* pair = array+i;\
    offset += (size_t )(pair->a);\
    fwrite(&offset, sizeof(size_t), 1, file);\
  }\
  for (size_t i = 0; i < len; i++){\
    struct __pointer_pair* pair = array+i;\
    fwrite((size_t *)(&pair->b), sizeof(uint8_t), (size_t)(pair->a), file);\
  }\
}


/*
 * WARN: use `MULTI_FILE_READ_FREE(array);`
 * WARN: assumption `fseek(file, 0, SEEK_SET);` or equivalant
*/
#define MULTI_FILE_READ(array, file){\
  assert(array != NULL || !"multi_file_read: invalid array");\
  assert(file != NULL || !"multi_file_read: invalid file");\
  size_t len;\
  fread(&len, sizeof(size_t), 1, file);\
  assert(len >= sizeof(uint64_t) || !"multi_file_read: invalid length");\
  struct __pointer_pair *array;\
  DARRAY_MAKE(struct __pointer_pair, array);\
  DARRAY_RESIZE(struct __pointer_pair, array, len);\
  for (size_t i = 0, prev = 0; i < len; i++){\
    size_t offset;\
    fread(&offset, sizeof(size_t), 1, file);\
    array[i].a = (void *)(offset - prev);\
    prev = offset;\
  }\
  for (size_t i = 0; i < len; i++){\
    struct __pointer_pair* pair = array+i;\
    size_t offset = (size_t)(pair->a);\
    pair->b = malloc(sizeof(uint8_t)*offset);\
    fread(pair->b, sizeof(uint8_t), offset, file);\
  }\
}

#define MULTI_FILE_READ_FREE(array){\
  assert(array != NULL || !"multi_file_read: invalid array");\
  for (size_t i = 0; i < *DARRAY_SIZE(return_value); i++) free(return_value[i].b);\
  DARRAY_FREE(return_value);\
}

/*
 * NOTE: Does NOT mofify stream position
 * WARN: use `free(array.b);`
*/
#define MULTI_FILE_GET(pair, file, index){\
  assert(file != NULL || !"multi_file_read: invalid file");\
  size_t len, offset[2];\
  size_t position = ftell(file);\
  fread(&len, sizeof(size_t), 1, file);\
  assert(len >= sizeof(uint64_t) || !"multi_file_read: invalid length");\
  if (index == 0) {\
    fread(offset+1, sizeof(size_t), 1, file);\
  } else {\
    fseek(file, (index-1)*sizeof(size_t), SEEK_CUR);\
    fread(&offset, sizeof(size_t), 2, file);\
    assert(offset[1] >= offset[0] || !"multi_file_read: invalid offset / invalid file");\
    offset[1] -= offset[0];\
  }\
  fseek(file, position + (len+1)*sizeof(size_t) + offset[0], SEEK_SET);\
  uint8_t *buff = (uint8_t *)malloc(sizeof(uint8_t)*offset[1]);\
  pair.a = (void *)offset[1];\
  pair.b = buff;\
  fread(pair.b, sizeof(uint8_t), offset[1], file);\
  fseek(file, position, SEEK_SET);\
}

#ifdef __cplusplus // if c++
}
#endif // end if c++
