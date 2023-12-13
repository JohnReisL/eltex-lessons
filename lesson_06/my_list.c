#include <stdlib.h>
#include <stdio.h>
#include "my_list.h"

#define INPUT_LINE "__________\b\b\b\b\b\b\b\b\b\b"

/* Это чтобы не вспоминать что там внутри \TODO Удалить
struct StudentInfo{
  char surename[64];
  unsigned long long record_book_number;
  char faculty_name[16];
  unsigned study_group_number;
};

struct MyTable {
  struct StudentInfo *p_stud_list[0];
};
//*/

static void GetMemToLine(struct MyTable *table) {
  
}

void InputToTable(struct MyTable *table) { //TODO закончить запись
  GetMemToLine(table);
  char buffer[sizeof(table->p_stud_list[0]->surename)];
  ull tmp;
  printf("Начало заполнения информации о студенте\n");

  printf("Введите фамилию : " INPUT_LINE);
  scanf("%s", &buffer);

  printf("Введите номер зачетки (число) : " INPUT_LINE);
  scanf("%ull", &tmp);

  printf("Введите название факультета : " INPUT_LINE);
  scanf("%s", &buffer);

  printf("Введите номер группы (число) : " INPUT_LINE);
  scanf("%ull", &tmp);
  
}

void FromFileToTable(struct MyTable *table) {
  
}

void FromTableToFile(char file_name[]) {
  
}

void PrintTableTable(struct MyTable *table) {

}

void SortByColumn(struct MyTable *table, unsigned colum_number) {

}

void FindByValue(struct MyTable *table,
		 unsigned colum_number,
		 char value[]) {
  
}

void DeleteLine(struct MyTable *table, unsigned line_number) {
  
}

void ChangeLine(struct MyTable *table, unsigned line_number) {
  
}

void MyTableDestructor(struct MyTable *table) {
  
}
