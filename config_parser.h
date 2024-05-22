#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structures.h"
#include "hash_map.h"


#define CONFIG_PARSER_SAVE(to_be_saved, options_file, length){\
  assert(options_file != NULL || !"File must not be NULL");\
  for (uint32_t _internal_variable_i = 0; _internal_variable_i < length; _internal_variable_i++){\
    if (to_be_saved[_internal_variable_i].a == NULL) fprintf(options_file, "\n");\
    else if (to_be_saved[_internal_variable_i].b == NULL) fprintf(options_file, "%s\n", (char *)to_be_saved[_internal_variable_i].a);\
    else fprintf(options_file, "%s = %s\n", (char *)to_be_saved[_internal_variable_i].a, (char *)to_be_saved[_internal_variable_i].b);\
  }\
}

#define CONFIG_PARSER_CONSUME_MAKE(options_struct, function_name, option_list...) \
options_struct function_name(DARRAY(struct _pointer_pair*) options){\
}

inline HMAP(struct _pointer_pair**) CONFIG_PARSER_PARSE(FILE *options_file){
  assert(options_file != NULL || !"File must not be NULL");
  struct _pointer_pair **array_to_return;
  HMAP_MAKE(array_to_return, 1024);
  fseek(options_file, 0, SEEK_END);
  uint32_t length_of_file;
  length_of_file = ftell(options_file);
  fseek(options_file, 0, SEEK_SET);
  char *buff = (char*)malloc(sizeof(char) * length_of_file);
  fread(buff, 1, length_of_file, options_file);
  char *pos = buff, *end = buff + length_of_file;

  while (pos < end){
    char *arg, *val;
    while ((*pos == ' ' || *pos == '\n' || *pos == '\t' || *pos == '\r') && pos < end) pos++;
    if (*pos == '#'){
      pos++;
      while (*pos != '\n' && pos < end) pos++;
      continue;
    }
    if (pos == end) break;
    arg = pos;
    while (*pos != '=' && *pos != '\n' && pos < end) pos++;
    if (pos == end || *pos == '\n') {
      *pos = '\0'; pos++;
      val = NULL;
      goto add;
    }
    val = pos+1;
    while (*(pos-1) == ' ' && pos > arg) pos--;
    if (pos == arg) arg = NULL;
    else *pos = '\0';
    while (*val == ' ' || *val == '\t' && val < end) val++;
    pos = val;
    while (*pos != '\n' && pos < end) pos++;
    *pos = '\0'; pos++;
    add:;
    HMAP_ADD(array_to_return, 0, arg, val);
  }
  return array_to_return;
}

#ifdef __cplusplus
};
#endif

