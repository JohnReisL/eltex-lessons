#include <stdio.h>
#include "my_list.h"

int main() {
  struct MyTable tmp = {0,0};
  Prepare(&tmp); //Обнулить переменные (конструктор)
  
  InputToTable(&tmp);
 
  MyTableDestructor(&tmp);
  return 0;
}
