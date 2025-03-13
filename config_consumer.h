#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "structures.h"
#include "hash_map.h"

#define CONFIG_CONSUMER_BIND_ALIAS(option_name, option_string)\
  HAMP_POP(_internal_variable_map, HMAP_STRING(option_string), option_string, strcmp(option_string, (char*)_internal_variable_i->key)==0, _internal_variable_pair);\
  _internal_variable_struct.option_name = _internal_variable_pair.a == NULL? NULL: _internal_variable_pair.b;

#define CONFIG_CONSUMER_BIND(option_name) CONFIG_PARSER_BIND_ALIAS(option_name, #option_name)

#define CONFIG_PARSER_CONSUME_MAKE(options_struct, function_name, option_list...)\
options_struct function_name(HMAP(struct _pointer_pair**) options){\
  static options_struct _internal_variable_struct;\
  struct _pointer_pair _internal_variable_pair;\
  option_list;\
  return options_struct;\
}

#ifdef __cplusplus
};
#endif

