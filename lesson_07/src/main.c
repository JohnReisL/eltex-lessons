#include <stdio.h>
#include <string.h>

#define SHOW_TASK 0
#define TASK "Реализация собственной функции cat\n"

int main(int argc, char *argv[]) {
#if SHOW_TASK
  printf("Задача: %s\n",TASK);
#endif
  
  if (argc > 3) { // Ну явно харам
    perror("Проблемка\nАрументов ... многоато ...\n");
    return -1;
  }
  if (argc == 2) { // Просто вывод
    FILE *fp = fopen(argv[1], "r");
    if (fp == 0) {
      perror("Файл нот опен, плиз файнд бай другой нэйм\n");
      return -3;
    }
    //Проверки окончены, работаем 
    char buf[BUFSIZ];
    while((fgets(buf, sizeof(buf), fp)) != NULL) {
      printf("%s", buf);
    }
    fclose(fp);
  } else if (argc == 3) { //пишем в файл
    if (strcmp(argv[1], "--w")) {
      perror("Проблемка\nВторой аргумент может быть только --w\n");
      return -2;
    } //если не вылетело, то прекрасно, работаем

    FILE *fp = fopen(argv[2], "w");
    char buf[BUFSIZ];
    if (fp) {
      while (scanf("%s", buf) != EOF) {
	fprintf(fp,"%s\n", buf);
      }
      
      fclose(fp);
    }
  } else if (argc == 1) { //Весело плюем текст абы куда
    char buf[BUFSIZ];
    while (scanf("%s", buf) != EOF) {
      fprintf(stdout,"%s\n", buf);
    } 
    
  }
  
  return 0;
}
