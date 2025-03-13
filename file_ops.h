#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define FILE_READ(file_ptr, var_buff){\
  assert(file_ptr != NULL || !"File must not be NULL");\
  fseek(file_ptr, 0, SEEK_END);\
  uint32_t _internal_variable_len;\
  _internal_variable_len = ftell(file_ptr);\
  fseek(file_ptr, 0, SEEK_SET);\
  var_buff = malloc(sizeof(char) * _internal_variable_len);\
  fread_unlocked(var_buff, 1, _internal_variable_len, file_ptr);\
}

#ifdef __cplusplus
};
#endif

