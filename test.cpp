#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dynamic_array.h"
#include "config_parser.h"

#define str(x) #x

// #define NDEBUG
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
    printf("|%s|%s|\n", (char *)i[j].a, (char *)(i[j].b));
  }
  assert(*size == 4 || !"Size must be 4");
  assert(strcmp((char *)i[0].a, "a") == 0 || !"First name must be 'a'");
  assert(strcmp((char *)i[0].b, "b") == 0 || !"First value must be 'b'");
  assert(strcmp((char *)i[1].a, "c") == 0 || !"Second name must be 'c'");
  assert(strcmp((char *)i[1].b, "d") == 0 || !"Second value must be 'd'");
  assert(strcmp((char *)i[2].b, "c") == 0 || !"Third value must be 'c'");
  assert(strcmp((char *)i[3].a, "asdas") == 0 || !"Fourth name must be 'asdas'");
}


int main() {
  return 0;
}
