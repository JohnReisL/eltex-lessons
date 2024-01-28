#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define SHOW_TASK 0
#define TASK "Используя доп материалы к лекции 3, напишите скрипт, который\
 удаляет выделенную область разделяемой памяти, используемый в sys1, sys2.\n"

int main() {
#if SHOW_TASK
  printf("Задача:\n%s\n\n",TASK);
#endif
  
  int *array;    /* Указатель на разделяемую память */
  int shmid;     /* IPC дескриптор для области разделяемой памяти */
  int new = 1;   /* Флаг необходимости инициализации элементов массива */
  char pathname[] = "sys1.c"; /* Имя файла, 
				 используемое для генерации ключа. Файл с таким 
				 именем должен существовать в текущей директории */
  key_t key;     /* IPC ключ */
  key_t key_2; 
  /* Генерируем IPC ключ из имени файла sys1.c в 
     текущей директории и номера экземпляра области 
     разделяемой памяти 0 */
  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }
  if ((key_2 = ftok(pathname, 1)) < 0) {
    printf("Can\'t generate key with same\n");
    exit(-1);
  }
  if (key == key_2) {
    printf("FAIL");
  }
  /* Пытаемся эксклюзивно создать разделяемую память для 
     сгенерированного ключа, т.е. если для этого ключа она
     уже существует, системный вызов вернет отрицательное 
     значение. Размер памяти определяем как размер массива 
     из трех целых переменных, права доступа 0666 – чтение
     и запись разрешены для всех */
  
  if ((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
    /* В случае ошибки пытаемся определить: возникла ли она
       из-за того, что сегмент разделяемой памяти уже существует
       или по другой причине */
    if (errno != EEXIST) {
      /* Если по другой причине – прекращаем работу */
      printf("Can\'t create shared memory\n");
      exit(-1);
    } else {
      /* Если из-за того, что разделяемая память уже 
	 существует, то пытаемся получить ее IPC 
	 дескриптор и, в случае удачи, сбрасываем флаг 
	 необходимости инициализации элементов массива */
      
      if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
	printf("Can\'t find shared memory\n");
	exit(-1);
      }
      new = 0;
    }
  }
  /* Пытаемся отобразить разделяемую память в адресное 
     пространство текущего процесса. Обратите внимание на то,
     что для правильного сравнения мы явно преобразовываем 
     значение -1 к указателю на целое.*/ 
  
  if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }
  /* В зависимости от значения флага new либо 
     инициализируем массив, либо увеличиваем 
     соответствующие счетчики */ 
  if (new) {
    array[0] = 1;
    array[1] = 0;
    array[2] = 1;
  } else {
    array[0] += 1;
    array[2] += 1;
  }
  /* Печатаем новые значения счетчиков, удаляем 
     разделяемую память из адресного пространства 
     текущего процесса и завершаем работу */
  printf("Program 1 was spawn %d times,program 2 - %d times, total - %d times\n", array[0], array[1], array[2]);
  if (shmdt(array) < 0) { 
    printf("Can't detach shared memory\n");
    exit(-1);
  }
  
  return 0;
}
