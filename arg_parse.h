#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(UNDEFINE_ARG_PARSE)
#define VOID 0
#define INT 1

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "limited_dynamic_array.h"

  // char** _internal_variable_scratch = var_pointer_pair_hmap[LDARRAY_SIZE(var_pointer_pair_hmap)];
#define ARG_PARSER_PARSE(argc, argv, var_pointer_pair_hmap) {\
  char *_internal_variable_buff;\
  LDARRAY_MAKE(_internal_variable_buff);\
  char *cur;\
  char **array;\
  DARRAY_MAKE(array);\
  DARRAY_RESIZE(array, argc*2);\
  size_t size = *(size_t*)DARRAY_SIZE(array);\
  size_t pos = 0;\
  while (pos < argc) {\
    cur = argv[pos];\
    if (cur[0] == '-') {\
      while (*cur != '=' && *cur != '\0') cur++;\
      if (cur[0] == '=') {\
        char *prior = cur;\
        while (*(prior-1) == ' ' || *(prior-1) == '\t' || *(prior-1) == '\n') prior--;\
        *prior = '\0';\
        cur++;\
        while (*cur == ' ' || *cur == '\t' || *cur == '\n') cur++;\
        array[size] = argv[pos];\
        (size)++;\
      }\
    }\
    array[size] = argv[pos];\
    (size)++;\
    pos++;\
  }\
}

#else
#undef UNDEFINE_ARG_PARSE
#undef VOID
#undef INT
#undef STRING
#undef ADD_ARG
#endif

#ifdef __cplusplus
};
#endif

