#include <signal.h>
#include <stdio.h>

void (*p)(int);

void my_handler (int nsig) {
  static int i = 0; // Не знаю зачем была глобально, тут логичнее

  switch (nsig) {
  case SIGINT:
    printf("Receive signal %d, CTRL-C pressed\n", nsig);
    break;
  case SIGQUIT:
    printf("Receive signal %d, CTRL-Z pressed\n", nsig); 
    i = i+1;
    if(i == 5) (void)signal(SIGQUIT, p);
    break;
  default:
    printf("[JRL] Unknown signal\n");
  }
  
}

int main (void) { 
  (void)signal(SIGINT, my_handler);
  (void)signal(SIGQUIT, my_handler);
  while(1);
  return 0;
}
