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
  
  int *array;
  int shmid;
  int new = 1;
  char pathname[] = "./README.md"; 
  key_t key;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }
  if ((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    } else {
      if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
	printf("Can\'t find shared memory\n");
	exit(-1);
      }
      new = 0;
    }
  }
  if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }
  if (new) {
    printf("Нот существует такой участок памяти, надо создать\n");
  } else {
  
    printf("Program 1 was spawn %d times,program 2 - %d times, total - %d times\n",
	   array[0], array[1], array[2]);
  }
  if (shmdt(array) < 0) { 
    printf("Can't detach shared memory\n");
    exit(-1);
  }

  struct shmid_ds buf;
  shmctl(shmid, IPC_RMID, &buf);
  printf("ХЛОБЫСЬ, данный очищены\n");
  //!< \TODO воткнуть ansi последовательность, чтобы было пафоснее (красный)
  
  
  return 0;
}
