#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void (*p)(int);

void my_handler (int nsig) {
  static int i = 0; // Не знаю зачем была глобально, тут логичнее
  int status;
  pid_t pid;

  switch (nsig) {
  case SIGINT:
    printf("Receive signal %d, CTRL-C pressed\n", nsig);
    break;
  case SIGQUIT: //!< \warning ! ВНИМАНИЕ ! сигнал подается через <ctrl> + <4>
    printf("Receive signal %d, CTRL-Z pressed (%d times)\n", nsig, i); 
    i = i+1;
    if(i == 5) {
      (void)signal(SIGQUIT, p);
    }
    break;
  case SIGCHLD:
    if((pid = waitpid(-1, &status, 0)) < 0){
      printf("Some error on waitpid errno = %d\n", errno);
    } else {
      if ((status & 0xff) == 0) {
	printf("Process %d was exited with status %d\n", 
	       pid, status >> 8);
      } else if ((status & 0xff00) == 0){
	printf("Process %d killed by signal %d %s\n", 
	       pid, status &0x7f,(status & 0x80) ? 
	       "with core file" : "without core file");
      }
    }
    break;
  case SIGKILL: // \TODO Разобрать как сделать реакцию на этот сигнал
    printf("Попытка убийства (успешно)");
    exit(0);
    break;
  default:
    printf("[JRL] Unknown signal\n");
  }
  
}

int main (void) { 
  (void)signal(SIGINT, my_handler);
  (void)signal(SIGQUIT, my_handler);
  
  (void) signal(SIGCHLD, my_handler);
  //! Ну тут просто обработчик встроенный, делать нечего
  // (void)signal(SIGINT, SIG_IGN);

  (void) signal(SIGKILL, my_handler);
  while(1);
  return 0;
}
