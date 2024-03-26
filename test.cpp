#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dynamic_array.h"
#include "config_parser.h"

#define str(x) #x

void test_darray(){
  char *array;
  DARRAY_MAKE(char, array);
  size_t* size = DARRAY_SIZE(array);
  assert(*size == 0 || !"Size must be 0 initially");
  DARRAY_ADD(char, array, 'a');
  assert(array[0] == 'a' || !"First element must be 'a'");
  DARRAY_ADD(char, array, 'b');
  assert(array[0] == 'a' || !"First element must be 'a'");
  assert(array[1] == 'b' || !"Second element must be 'b'");
}

void test_variable_saver(){
  char s[] = "\n\
a = b\n\
c = d\n\
# sda\n\
\n\
#asd\n\
\n\
\n\
 = c\n\
asdas\n\
\n\
#saa = asd\n\
\n\
  ";
  FILE *file = fmemopen((void *)s, sizeof(s), "r");
  auto i = __load_variables(file);
  size_t* size = DARRAY_SIZE(i);
  for (size_t j = 0; j < *size; j++){
    printf("|%s|%s|\n", i[j].name, i[j].value);
  }
  assert(*size == 4 || !"Size must be 4");
  assert(strcmp(i[0].name, "a") == 0 || !"First name must be 'a'");
  assert(strcmp(i[0].value, "b") == 0 || !"First value must be 'b'");
  assert(strcmp(i[1].name, "c") == 0 || !"Second name must be 'c'");
  assert(strcmp(i[1].value, "d") == 0 || !"Second value must be 'd'");
  assert(strcmp(i[2].value, "c") == 0 || !"Third value must be 'c'");
  assert(strcmp(i[3].name, "asdas") == 0 || !"Fourth name must be 'asdas'");
}

int main() {
  test_variable_saver();
  return 0;
}
