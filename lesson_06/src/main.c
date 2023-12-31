#include <stdio.h>
#include "../include/my_list.h"

#define SHOW_TASK 1
#define TASK "Определить структурированный тип и набор функций\
 для работы с таблицей записей, реализованной в массиве структур.\
 В перечень функций входят:\n\
· ввод записи таблицы с клавиатуры;\n\
· загрузка и сохранение таблицы в текстовом файле;\n\
· просмотр таблицы;\n\
· сортировка таблицы в порядке возрастания заданного поля;\n\
· поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;\n\
· удаление записи;\n\
· изменение (редактирование) записи;\n\
· вычисление с проверкой и использованием всех записей по заданному условию (номер группы)\n\
Перечень полей структурированной переменной: Фамилия, номер зачетной книжки, факультет, группа.\n"

int main() {
#if SHOW_TASK
  printf("Задача:\n%s\n\n",TASK);
#endif
  
  printf("Защиты \"от дурака\" нет, значения не проверяются\n");
  printf("Корректность воода данных на плечах вводящего\n");
  
  struct MyTable tmp = {0,0};
  Prepare(&tmp); //Обнулить переменные (конструктор)
  
  /* InputToTable(&tmp); */

  FromFileToTable(&tmp, "example.csv");
  
  FromTableToFile(&tmp, "written.csv") ;

  SortByColumn(&tmp, 1);
  /* PrintTableTable(struct MyTable *table); */

  /* SortByColumn(struct MyTable *table, unsigned colum_number); */
  /* FindByValue(struct MyTable *table, */
  /* 	      unsigned colum_number, */
  /* 	      char value[]); */

  DeleteLine(&tmp);

  ChangeLine(&tmp);

  
  printf("Вывод таблицы:\n");
  PrintTableTable(&tmp);
  
  MyTableDestructor(&tmp);
  return 0;
}
