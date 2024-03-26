#pragma once

#ifdef __cplusplus // if c++
extern "C" {
#endif // end if c++

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"
//default_callback_manager

inline void __parsable_arguments(char * arg_name, void * callback_or_arg_value, size_t argc = 0, size_t* start = NULL){
  //argument_start, argument_end, start, argc;
  static void** args = (void **)malloc(sizeof(void *)*1024*4);
  static size_t total = 1024;
  static size_t filled = 0;
  if (!arg_name) {
    static void *call = NULL;
    if (start && call) ((void(*)(char*, size_t, size_t*))call)((char*)callback_or_arg_value, argc, start);
  }
  const size_t len = strlen(arg_name);
  if (start == NULL){
    if (filled == total) args = (void**)realloc((void*) args, (total += 1024)*sizeof(void *)*4);
    args[ filled*4 ] = arg_name;
    args[filled*4+1] = (void *)len;
    strncpy((char *)(args+filled*4+2), arg_name, len>sizeof(void *)?sizeof(void*):len);
    args[filled*4+3] = callback_or_arg_value;
    ++filled;
  }else {
    void *tocomp;
    strncpy((char*)&tocomp, arg_name, len>sizeof(void *)?sizeof(void*):len);
    char **args_vals = (char **)malloc(sizeof(char *)*1024);
    size_t args_vals_filled = 1, args_vals_total = 1023;// not 1024, to keep 1 space empty at the end for null
    args_vals[0] = (char *)callback_or_arg_value;
    if (callback_or_arg_value){
      for (char* vals=(char *)callback_or_arg_value; *vals !='\0'; vals++) {
        if (*vals == ',') {
          *vals = '\0';
          if (args_vals_filled == total) args_vals = (char**)realloc((void*) args_vals, (args_vals_total += 1024)*sizeof(char **));
          args_vals[args_vals_filled] = ++vals;
        }
      }
      args_vals[args_vals_filled] = NULL;
    }
    for (size_t i = 0; i < filled; i++){
      if ((void *)len==args[i*4+1]){
        tocomp = NULL;
        strncpy((char *)&tocomp, arg_name, len>sizeof(void *)?sizeof(void*):len);
        if (tocomp==args[i*4+2]){
          if (len<=sizeof(void*)? true: 0==strcmp(arg_name-sizeof(void*),(char*)args[i*4]-sizeof(void*))){
            ( (void(*)(char*, char**, size_t, size_t*))args[i*4+3] )(arg_name, args_vals, argc, start);
            break;
          }
        }
      }
    }
    free(args_vals);
  }
}

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


#ifdef __cplusplus // if c++
}; // namespace arg_parser
#endif // end if c++

