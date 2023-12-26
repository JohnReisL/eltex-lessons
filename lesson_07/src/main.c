#include <stdio.h>
#include <string.h>

#define SHOW_TASK 1
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
  } else if (argc == 1) { //пишем в файл
    /* if ((strlen(argv[1]) != 1) || (*argv[1] != '>')) { */
    /*   perror("Проблемка\nВторой аргумент может быть только >\n"); */
    /*   return -2; */
    /* } //если не вылетело, то прекрасно, работаем */

    //FILE *fp = fopen(argv[2], "w");
    /* char buf[BUFSIZ]; */
    /* do { */
    /* scanf("%s", buf); */
    /* printf("%s", buf); */
    /* } while (buf[0] != 0); */
    //fclose(fp);
  }
  
  return 0;
}
