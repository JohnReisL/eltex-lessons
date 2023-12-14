#ifndef MY_LIST
#define MY_LIST

//! При выносе в другой файл создавало проблемы, возможно потом мсправлю \TODO
typedef unsigned long long ull;

struct StudentInfo{
  char surename[32];
  char faculty_name[32];
  ull record_book_number;
  ull study_group_number;
};

struct MyTable {
  struct StudentInfo *p_stud_list;
  ull counter;
};

void InputToTable(struct MyTable *table);

void FromFileToTable(struct MyTable *table);

void FromTableToFile(char file_name[]);

void PrintTableTable(struct MyTable *table);

void SortByColumn(struct MyTable *table, unsigned colum_number);

void FindByValue(struct MyTable *table,
		 unsigned colum_number,
		 char value[]);

void DeleteLine(struct MyTable *table, unsigned line_number);

void ChangeLine(struct MyTable *table, unsigned line_number);

void Prepare(struct MyTable *table);

void MyTableDestructor(struct MyTable *table);


#endif
