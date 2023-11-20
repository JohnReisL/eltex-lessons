#include <stdio.h>
#include <string.h>


int main() {
  char str[64];
  scanf("%s",&str);
  printf("Ищем по имени %s\n", str);
  strcat(str, ":"); // сепарирующий символ в формате файла
  
  char * filename = "/etc/passwd";
  char buffer[256];
  FILE *fp = fopen(filename, "r");
  if(fp) {
    while((fgets(buffer, 256, fp)) != NULL) {
      /* printf("%s\n\n\n", buffer); */

      unsigned is_here = 1; //вообще был bool
      for(int i = 0; str[i] != '\0'; ++i) {
	if (str[i] != buffer[i]) {
	  is_here = 0;
	  break;
	}
      }
      if (is_here) {
	char name[128];
	unsigned int column = 0;
	for(int i = 0; buffer[i] != '\0'; ++i) {
	  if (buffer[i] == ':') {
	    ++column;
	    if (column > 4) break;
	    else continue;
	  }
	  if (column == 4) {
	    char tmp[2] = {buffer[i], 0}; //!< пока костыль, но работает
	    strcat(name, tmp);
	  }
	  
	}
	printf("Имя пользователя может быть: %s\n", name);
	//!< Без доп. проверок "на дурака", запятые будут
      }
      
    }
    fclose(fp);
  } else {
    printf("Файл не был открыт\n");
  }

  
  
  
  return 0;
}
