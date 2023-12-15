#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/my_list.h"

#define INPUT_LINE "__________\b\b\b\b\b\b\b\b\b\b"

static void GetMemToLine(struct MyTable *table) {
  if (0 == table->counter) {
    ++table->counter;
    table->p_stud_list = calloc(1, sizeof(struct StudentInfo));
  } else {
    table->p_stud_list =
      realloc(table->p_stud_list,
	      ++table->counter * sizeof(struct StudentInfo));
  }
}

static void DelMemLastLine(struct MyTable *table) {
  if (0 == table->counter) {
    return;
  } else {
    table->p_stud_list =
      realloc(table->p_stud_list,
	      --table->counter * sizeof(struct StudentInfo));
  }
}

void InputToTable(struct MyTable *table) { //TODO закончить запись
  GetMemToLine(table);
  
  char buffer[sizeof(table->p_stud_list->surename)];
  ull tmp;
  printf("Начало заполнения информации о студенте\n");
  
  printf("Введите фамилию : " INPUT_LINE);
  scanf("%s", buffer);
  strcpy(table->p_stud_list[table->counter - 1].surename, buffer);
 
  printf("Введите номер зачетки (число) : " INPUT_LINE);
  scanf("%llu", &tmp);
  table->p_stud_list[table->counter - 1].record_book_number = tmp;

  printf("Введите название факультета : " INPUT_LINE);
  scanf("%s", buffer);
  strcpy(table->p_stud_list[table->counter - 1].faculty_name, buffer);

  printf("Введите номер группы (число) : " INPUT_LINE);
  scanf("%llu", &tmp);
  table->p_stud_list[table->counter - 1].study_group_number = tmp;
  
}

void FromFileToTable(struct MyTable *table, char file_name[]) {
  char buffer[256];
  char word[64];
  FILE *fp = fopen(file_name, "r");
  if(fp) {
    while((fgets(buffer, sizeof(buffer), fp)) != NULL) {
      GetMemToLine(table); // строка есть, нужна память      
      for (int i = 0; i < 4; ++i) {
	for (int j = 0; j < strlen(buffer); ++j) {
	  if (buffer[j] == ',') {
	    word[j] = '\0';
	    strcpy(buffer, &buffer[j] +1);
	    break;
	  } else {
	    word[j] = buffer[j];
	  }
	}
	if(i == 0) {
	  strcpy(table->p_stud_list[table->counter - 1].surename, word);
	} else if (i == 1) {
	  table->p_stud_list[table->counter - 1].record_book_number
	    = atoi(word);  
	} else if (i == 2) {
	  strcpy(table->p_stud_list[table->counter - 1].faculty_name, word);
	} else if (i == 3) {
	  table->p_stud_list[table->counter - 1].study_group_number
	    = atoi(word);
	}
      }      //вставляем на место
    
    }
    fclose(fp);
  } else {
    printf("Проблемка: файл не был открыт\n");
    return;
  }
}

void FromTableToFile(struct MyTable *table,char file_name[]) {
  FILE *fp = fopen(file_name, "w");
  if(fp) {
    for(int i = 0; i < table->counter; ++i) {
      char buffer[64];
      sprintf(buffer, "%llu", table->p_stud_list[i].record_book_number);
      fputs(table->p_stud_list[i].surename, fp);
      fputs(",", fp);
      fputs(buffer, fp);
      fputs(",", fp);
      fputs(table->p_stud_list[i].faculty_name, fp);
      fputs(",", fp);
      sprintf(buffer, "%llu", table->p_stud_list[i].study_group_number);
      fputs(buffer, fp);
      fputs("\n", fp);

    }
    fclose(fp);
  } else {
    printf("Проблемка: файл не может быть записан\n");
    return;
  }
}

void PrintTableTable(struct MyTable *table) {
  for (ull i = 0;
       i < (table->counter);
       ++i) {
    printf("№%llu | Фамииля : %s, зачетка : %llu, факультет : %s, группа : %llu\n",
	   i,
	   table->p_stud_list[i].surename,
	   table->p_stud_list[i].record_book_number,
	   table->p_stud_list[i].faculty_name,
	   table->p_stud_list[i].study_group_number);
  }
}


void SortByColumn(struct MyTable *table, unsigned colum_number) {}

void FindByValue(struct MyTable *table,
		 unsigned colum_number,
		 char value[]) {}

void DeleteLine(struct MyTable *table) {
  PrintTableTable(table);
  ull line_to_delete = -1;
  printf("Какую строку вы бы хотели удалить(номер слева)?");
  scanf("%llu", &line_to_delete);

  if (line_to_delete >= table->counter) {
    printf("3гогг: неверное значение :р\n");
    return;
  }

  for (int i = line_to_delete; i < (table->counter - 2); ++i) {
    table->p_stud_list[i] = table->p_stud_list[i + 1];
  }
  
  DelMemLastLine(table);
}

void ChangeLine(struct MyTable *table) {
  PrintTableTable(table);
  ull line_to_change = -1;
  printf("Какую строку вы бы хотели изменить(номер слева)?");
  scanf("%llu", &line_to_change);

  if (line_to_change >= table->counter) {
    printf("3гогг: неверное значение :р\n");
    return;
  }

  char buffer[sizeof(table->p_stud_list->surename)];
  ull tmp;
  printf("Начало заполнения информации о студенте\n");
  
  printf("Введите фамилию : " INPUT_LINE);
  scanf("%s", buffer);
  strcpy(table->p_stud_list[line_to_change].surename, buffer);
  
  printf("Введите номер зачетки (число) : " INPUT_LINE);
  scanf("%llu", &tmp);
  table->p_stud_list[line_to_change].record_book_number = tmp;
  
  printf("Введите название факультета : " INPUT_LINE);
  scanf("%s", buffer);
  strcpy(table->p_stud_list[line_to_change].faculty_name, buffer);
  
  printf("Введите номер группы (число) : " INPUT_LINE);
  scanf("%llu", &tmp);
  table->p_stud_list[line_to_change].study_group_number = tmp;
  
}

void Prepare(struct MyTable *table) {
  table->p_stud_list = 0;
  table->counter = 0;
}


void MyTableDestructor(struct MyTable *table) {
  free(table->p_stud_list);
}
