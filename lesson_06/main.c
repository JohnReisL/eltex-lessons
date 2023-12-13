#include <stdio.h>
#include "my_list.h"

int main() {
  struct MyTable tmp;
  InputToTable(&tmp);

 
  MyTableDestructor(&tmp);
  return 0;
}
