#pragma once

#ifdef __cplusplus // if c++
extern "C" {
#endif // end if c++

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structures.h"
#include "dynamic_array.h"


#define __SAVE_VARIABLES_TO_FILE(to_be_saved, options_file, length){\
  assert(options_file != NULL || !"File must not be NULL");\
  for (size_t i = 0; i < length; i++){\
    fprintf(options_file, "%s = %s\n", (char *)to_be_saved[i].a, (char *)to_be_saved[0].b);\
  }\
}

__DARRAY(struct __pointer_pair*) __load_variables(FILE *options_file){
  assert(options_file != NULL || !"File must not be NULL");
  size_t length_of_file;
  struct __pointer_pair *array_to_return = NULL;
  DARRAY_MAKE(struct __pointer_pair, array_to_return);
  DARRAY_RESIZE(struct __pointer_pair, array_to_return, 1024-1);
  fseek(options_file, 0, SEEK_END);
  length_of_file = ftell(options_file);
  fseek(options_file, 0, SEEK_SET);
  char *buff = (char*)malloc(sizeof(char) * length_of_file);
  fread(buff, 1, length_of_file, options_file);
  char *pos = buff, *end = buff + length_of_file;

  while (pos < end){
    char *arg, *val;
    while ((*pos == ' ' || *pos == '\n' || *pos == '\t' || *pos == '\0') && pos < end) pos++;
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
    struct __pointer_pair v = {arg, val};
    DARRAY_ADD(struct __pointer_pair, array_to_return, v);
  }
  return array_to_return;
}

#ifdef __cplusplus // if c++
}; // namespace arge parser
#endif // end if c++

