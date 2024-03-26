#pragma once

#ifdef __cplusplus // if c++
extern "C" {
#endif // end if c++

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "structures.h"
#include "dynamic_array.h"

__DARRAY(struct __pointer_pair *) __create_multi_file(){
  struct __pointer_pair * array;
  DARRAY_MAKE(struct __pointer_pair, array);
  return array;
}

void __multi_file_add(__DARRAY(struct __pointer_pair *) array, const uint8_t* value, const size_t len){
  struct __pointer_pair pair{(void *)len, (void *) value};
  DARRAY_ADD(struct __pointer_pair, array, pair)
}

void __multi_file_flush(__DARRAY(struct __pointer_pair *) array, FILE *file){
  size_t *size = DARRAY_SIZE(array);
  fwrite(size, sizeof(size_t), 1, file);
  const size_t len = *size;
  for (size_t i = 0, offset = 0; i < len; i++){
    struct __pointer_pair* pair = array+i;
    offset += (size_t )(pair->a);
    fwrite(&offset, sizeof(size_t), 1, file);
  }
  for (size_t i = 0; i < len; i++){
    struct __pointer_pair* pair = array+i;
    fwrite((size_t *)(&pair->b), sizeof(uint8_t), (size_t)(pair->a), file);
  }
}

__DARRAY(struct __pointer_pair *) __multi_file_read(FILE *file){
  fseek(file, 0, SEEK_SET);
  size_t len;
  fread(&len, sizeof(size_t), 1, file);
  assert(len >= sizeof(uint64_t) || !"multi_file_read: invalid length");
  struct __pointer_pair *array;
  DARRAY_MAKE(struct __pointer_pair, array);
  DARRAY_RESIZE(struct __pointer_pair, array, len);
  for (size_t i = 0, prev = 0; i < len; i++){
    size_t offset;
    fread(&offset, sizeof(size_t), 1, file);
    array[i].a = (void *)(offset - prev);
    prev = offset;
  }
  for (size_t i = 0; i < len; i++){
    struct __pointer_pair* pair = array+i;
    size_t offset = (size_t)(pair->a);
    pair->b = malloc(sizeof(uint8_t)*offset);
    fread(pair->b, sizeof(uint8_t), offset, file);
  }
  return array;
}

#ifdef __cplusplus // if c++
}
#endif // end if c++
