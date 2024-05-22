#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(UNDEFINE_ARG_PARSE)
#define VOID 0
#define INT 1

#define ARG_NEXT() ;

#define ARG_ADD(argname, var, consume)

#else
#undef UNDEFINE_ARG_PARSE
#undef VOID
#undef INT
#undef STRING
#undef ADD_ARG
#endif





#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

inline __DARRAY(char**) __parse_arguments(const size_t argc, char** argv) {
  char *cur;
  char **array;
  DARRAY_MAKE(char *, array);
  DARRAY_RESIZE(cahr*, array, argc*2);
  size_t *size = DARRAY_SIZE(array);
  size_t pos = 0;
  while (pos < argc) {
    cur = argv[pos];
    if (cur[0] == '-') {
      while (*cur != '=' && *cur != '\0') cur++;
      if (cur[0] == '=') {
        char *prior = cur;
        while (*(prior-1) == ' ' || *(prior-1) == '\t' || *(prior-1) == '\n') prior--;
        *prior = '\0';
        cur++;
        while (*cur == ' ' || *cur == '\t' || *cur == '\n') cur++;
        array[*size] = argv[pos];
        (*size)++;
      }
    }
    array[*size] = argv[pos];
    (*size)++;
    pos++;
  }
  return array;
}

#ifdef __cplusplus
};
#endif

