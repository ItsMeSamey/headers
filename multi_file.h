#pragma once

#ifdef __cplusplus // if c++
extern "C" {
#endif // end if c++

#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "structures.h"
#include "dynamic_array.h"

/*
 * WARN: use `DARRAY_FREE(array);`
*/
#define MULTI_FILE_MAKE(array) DARRAY_MAKE(array);\

#define  MULTI_FILE_ADD(array, value, len){\
  assert(array != NULL || !"multi_file_read: invalid array");\
  assert(value != NULL || !"multi_file_read: invalid value");\
  DARRAY_ADD(array, {(void *)len, (void *) value})\
}

#define MULTI_FILE_WRITE(array, file){\
  assert(array != NULL || !"multi_file_read: invalid array");\
  assert(file != NULL || !"multi_file_read: invalid file");\
  fwrite_unlocked(DARRAY_SIZE(array), sizeof(uint32_t), 1, file);\
  const uint32_t _internal_variable_len = *DARRAY_SIZE(array);\
  for (uint32_t _internal_variable_i = 0, _internal_variable_offset = 0; _internal_variable_i < _internal_variable_len; _internal_variable_i++){\
    _internal_variable_offset += (uint32_t )((array+_internal_variable_i)->a);\
    fwrite_unlocked(&_internal_variable_offset, sizeof(uint32_t), 1, file);\
  }\
  for (uint32_t _internal_variable_i = 0; _internal_variable_i < _internal_variable_len; _internal_variable_i++){\
    fwrite_unlocked((array+_internal_variable_i)->b, sizeof(uint8_t), (uint32_t)((array+_internal_variable_i)->a), file);\
  }\
}

/*
 * WARN: use `MULTI_FILE_READ_FREE(array);`
 * WARN: assumption `fseek(file, 0, SEEK_SET);` or equivalant
*/
#define MULTI_FILE_READ(array, file){\
  assert(array != NULL || !"multi_file_read: invalid array");\
  assert(file != NULL || !"multi_file_read: invalid file");\
  uint32_t _internal_variable_len;\
  fread_unlocked(&_internal_variable_len, sizeof(uint32_t), 1, file);\
  assert(_internal_variable_len >= sizeof(uint64_t) || !"multi_file_read: invalid length");\
  DARRAY_MAKE(array);\
  DARRAY_RESIZE(array, _internal_variable_len);\
  for (uint32_t _internal_variable_i = 0, _internal_variable_prev = 0; _internal_variable_i < _internal_variable_len; _internal_variable_i++){\
    uint32_t _internal_variable_offset;\
    fread_unlocked(&_internal_variable_offset, sizeof(uint32_t), 1, file);\
    array[_internal_variable_i].a = (void *)(_internal_variable_offset - _internal_variable_prev);\
    _internal_variable_prev = _internal_variable_offset;\
  }\
  for (uint32_t _internal_variable_i = 0; _internal_variable_i < _internal_variable_len; _internal_variable_i++){\
    (array+_internal_variable_i)->b = malloc(sizeof(uint8_t)*(size_t)((array+_internal_variable_i)->a));\
    fread_unlocked((array+_internal_variable_i)->b, sizeof(uint8_t), (size_t)((array+_internal_variable_i)->a), file);\
  }\
}

#define MULTI_FILE_READ_FREE(array){\
  assert(array != NULL || !"multi_file_read: invalid array");\
  for (uint32_t _internal_variable_i = 0; _internal_variable_i < *DARRAY_SIZE(array); i++) free(array[_internal_variable_i].b);\
  DARRAY_FREE(array);\
}

/*
 * NOTE: Does NOT mofify stream position
 * WARN: use `free(array.b);`
*/
#define MULTI_FILE_GET(pair, file, index){\
  assert(file != NULL || !"multi_file_read: invalid file");\
  uint32_t _internal_variable_len, _internal_variable_offset[2];\
  uint32_t _internal_variable_position = ftell(file);\
  fread_unlocked(&_internal_variable_len, sizeof(uint32_t), 1, file);\
  assert(_internal_variable_len >= sizeof(uint64_t) || !"multi_file_read: invalid length");\
  assert(_internal_variable_len >= index || !"multi_file_read: invalid index / invalid file");\
  if (index == 0) {\
    _internal_variable_offset[0] = 0; fread_unlocked(_internal_variable_offset+1, sizeof(uint32_t), 1, file);\
  } else {\
    fseek(file, (index-1)*sizeof(uint32_t), SEEK_CUR);\
    fread_unlocked(&_internal_variable_offset, sizeof(uint32_t), 2, file);\
    assert(_internal_variable_offset[1] >= _internal_variable_offset[0] || !"multi_file_read: invalid offset / invalid file");\
    _internal_variable_offset[1] -= _internal_variable_offset[0];\
  }\
  fseek(file, _internal_variable_position + (_internal_variable_len+1)*sizeof(uint32_t) + _internal_variable_offset[0], SEEK_SET);\
  uint8_t *_internal_variable_buff = (uint8_t *)malloc(sizeof(uint8_t)*_internal_variable_offset[1]);\
  pair.a = (void *)_internal_variable_offset[1];\
  pair.b = _internal_variable_buff;\
  fread_unlocked(pair.b, sizeof(uint8_t), _internal_variable_offset[1], file);\
  fseek(file, _internal_variable_position, SEEK_SET);\
}

#ifdef __cplusplus // if c++
}
#endif // end if c++
