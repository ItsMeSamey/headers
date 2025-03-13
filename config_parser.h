#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structures.h"
#include "file_ops.h"
#include "hash_map.h"

#define CONFIG_PARSER_SAVE(to_be_saved, options_file, length){\
  assert(options_file != NULL || !"File must not be NULL");\
  for (uint32_t _internal_variable_i = 0; _internal_variable_i < length; _internal_variable_i++){\
    if (to_be_saved[_internal_variable_i].a == NULL) fprintf(options_file, "\n");\
    else if (to_be_saved[_internal_variable_i].b == NULL) fprintf(options_file, "%s\n", (char *)to_be_saved[_internal_variable_i].a);\
    else fprintf(options_file, "%s = %s\n", (char *)to_be_saved[_internal_variable_i].a, (char *)to_be_saved[_internal_variable_i].b);\
  }\
}

#define CONFIG_PARSER_PARSE(options_file, var_pointer_pair_hmap){\
  void* _internal_variable_buff;\
  FILE_READ(options_file, _internal_variable_buff);\
  char *_internal_variable_pos = _internal_variable_buff, *_internal_variable_end = (char*)_internal_variable_buff + _internal_variable_len;\
  while (_internal_variable_pos < _internal_variable_end){\
    char *_internal_variable_arg, *_internal_variable_val;\
    while ((*_internal_variable_pos == ' ' || *_internal_variable_pos == '\n' || *_internal_variable_pos == '\t' || *_internal_variable_pos == '\r') && _internal_variable_pos < _internal_variable_end) _internal_variable_pos++;\
    if (*_internal_variable_pos == '#'){\
      _internal_variable_pos++;\
      while (*_internal_variable_pos != '\n' && _internal_variable_pos < _internal_variable_end) _internal_variable_pos++;\
      continue;\
    }\
    if (_internal_variable_pos == _internal_variable_end) break;\
    _internal_variable_arg = _internal_variable_pos;\
    while (*_internal_variable_pos != '=' && *_internal_variable_pos != '\n' && _internal_variable_pos < _internal_variable_end) _internal_variable_pos++;\
    if (_internal_variable_pos == _internal_variable_end || *_internal_variable_pos == '\n') {\
      *_internal_variable_pos = '\0'; _internal_variable_pos++;\
      _internal_variable_val = NULL;\
      goto _internal_variable_CONFIG_PARSER_PARSE_1;\
    }\
    _internal_variable_val = _internal_variable_pos+1;\
    while (*(_internal_variable_pos-1) == ' ' && _internal_variable_pos > _internal_variable_arg) _internal_variable_pos--;\
    if (_internal_variable_pos == _internal_variable_arg) _internal_variable_arg = NULL;\
    else *_internal_variable_pos = '\0';\
    while (*_internal_variable_val == ' ' || *_internal_variable_val == '\t' && _internal_variable_val < _internal_variable_end) _internal_variable_val++;\
    _internal_variable_pos = _internal_variable_val;\
    while (*_internal_variable_pos != '\n' && _internal_variable_pos < _internal_variable_end) _internal_variable_pos++;\
    *_internal_variable_pos = '\0'; _internal_variable_pos++;\
    _internal_variable_CONFIG_PARSER_PARSE_1: HMAP_ADD(var_pointer_pair_hmap, HMAP_STRING(_internal_variable_arg), _internal_variable_arg, _internal_variable_val);\
  }\
}

#ifdef __cplusplus
};
#endif

