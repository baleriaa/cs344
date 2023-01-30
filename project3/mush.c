// my own shell program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
  char prompt[] = "mush> ";
  char *token;
  char buffer[2048];
  char *words[128];
  int i = 0;
  
  printf("%s", prompt);
  fgets(buffer, sizeof buffer, stdin);
  if ((token = strtok(buffer, " \t\r\n")) != NULL) {
    do {
      printf("%s\n", token);
      words[i++] = token;
    } while ((token = strtok(NULL, " \t\r\n")) != NULL);
  }
  words[i++] = NULL;
  execvp(words[0], words);
}