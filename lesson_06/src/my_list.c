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

static unsigned SrtingBiggerThen(char const str1[], char const str2[]) {
  for (unsigned i = 0; (str1[i] != 0) && (str2[i] != 0); ++i) {
    if(str1[i] > str2[i]) {
      return 1;
    } else if (str1[i] < str2[i]) {
      return 0;
    } 
  }
  return 0;
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


void SortByColumn(struct MyTable *table, unsigned colum_number) {
  struct StudentInfo tmp;
  unsigned noSwap;
  if (colum_number == 0) { //фамилия
    for (int i = table->counter - 1; i >= 0; i--) {
      noSwap = 1;
      for (int j = 0; j < i; j++) {
	if (SrtingBiggerThen(table->p_stud_list[j].surename,
			     table->p_stud_list[j + 1].surename)) {
	  tmp = table->p_stud_list[j];
	  table->p_stud_list[j] = table->p_stud_list[j + 1];
	  table->p_stud_list[j + 1] = tmp;
	  noSwap = 0;
	}
      }
      if (noSwap == 1)
	break;
    }
    
  } else if (colum_number == 1) { // зачетка
    for (int i = table->counter - 1; i >= 0; i--) {
      noSwap = 1;
      for (int j = 0; j < i; j++) {
	if (table->p_stud_list[j].record_book_number >
	    table->p_stud_list[j + 1].record_book_number) {
	  tmp = table->p_stud_list[j];
	  table->p_stud_list[j] = table->p_stud_list[j + 1];
	  table->p_stud_list[j + 1] = tmp;
	  noSwap = 0;
	}
      }
      if (noSwap == 1)
	break;
    }
  } else if (colum_number == 2) { // факультет
    for (int i = table->counter - 1; i >= 0; i--) {
      noSwap = 1;
      for (int j = 0; j < i; j++) {
	if (SrtingBiggerThen(table->p_stud_list[j].faculty_name,
			     table->p_stud_list[j + 1].faculty_name)) {
	  tmp = table->p_stud_list[j];
	  table->p_stud_list[j] = table->p_stud_list[j + 1];
	  table->p_stud_list[j + 1] = tmp;
	  noSwap = 0;
	}
      }
      if (noSwap == 1)
	break;
    }
  } else if (colum_number == 3) { // номер учебной группы
    for (int i = table->counter - 1; i >= 0; i--) {
      noSwap = 1;
      for (int j = 0; j < i; j++) {
	if (table->p_stud_list[j].study_group_number >
	    table->p_stud_list[j + 1].study_group_number) {
	  tmp = table->p_stud_list[j];
	  table->p_stud_list[j] = table->p_stud_list[j + 1];
	  table->p_stud_list[j + 1] = tmp;
	  noSwap = 0;
	}
      }
      if (noSwap == 1)
	break;
    }
  } else {
    printf("Число вне диапазона (доступны 0-3)\n");
  }
}

void FindByValue(struct MyTable *table,
		 unsigned colum_number,
		 char value[]) {
  char find_str[32];
  ull find_num;
  if ((colum_number == 1) || (colum_number == 3)) {
    strcpy(find_str, value);
  } else if ((colum_number == 0) || (colum_number == 2)) {
    find_num = atoi(value);
  } else {
    printf("wrong value of column\n\n");
    return;
  }
  
  unsigned counter = 0;
  if (colum_number == 0) {
    for(int i = 0; i < table->counter; ++i) {
      if (table->p_stud_list[i].surename == find_str) {
	printf("Фамииля : %s, зачетка : %llu, факультет : %s, группа : %llu\n",
	       table->p_stud_list[i].surename,
	       table->p_stud_list[i].record_book_number,
	       table->p_stud_list[i].faculty_name,
	       table->p_stud_list[i].study_group_number);
      }
    }
  } else if (colum_number == 1) {
    for(int i = 0; i < table->counter; ++i) {
      if (table->p_stud_list[i].record_book_number == find_num) {
	printf("Фамииля : %s, зачетка : %llu, факультет : %s, группа : %llu\n",
	       table->p_stud_list[i].surename,
	       table->p_stud_list[i].record_book_number,
	       table->p_stud_list[i].faculty_name,
	       table->p_stud_list[i].study_group_number);
      }
    }
  } else if (colum_number == 2) {
    for(int i = 0; i < table->counter; ++i) {
      if (table->p_stud_list[i].faculty_name == find_str) {
	printf("Фамииля : %s, зачетка : %llu, факультет : %s, группа : %llu\n",
	       table->p_stud_list[i].surename,
	       table->p_stud_list[i].record_book_number,
	       table->p_stud_list[i].faculty_name,
	       table->p_stud_list[i].study_group_number);
      }
    }
  } else if (colum_number == 3) {
    for(int i = 0; i < table->counter; ++i) {
      if (table->p_stud_list[i].study_group_number == find_num) {
	printf("Фамииля : %s, зачетка : %llu, факультет : %s, группа : %llu\n",
	       table->p_stud_list[i].surename,
	       table->p_stud_list[i].record_book_number,
	       table->p_stud_list[i].faculty_name,
	       table->p_stud_list[i].study_group_number);
      }
    }
  }

  if (!counter) {
    printf("Не было найдено таких значений\n");
  }
}

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

void FindGroupAndChange(struct MyTable *table, ull group_was, ull group_be) {
    for(int i = 0; i < table->counter; ++i) {
      if (table->p_stud_list[i].record_book_number == group_was) {
	table->p_stud_list[i].record_book_number = group_be;
      }
    }
}
