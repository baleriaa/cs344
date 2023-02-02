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
  fflush(stdout);
  fgets(buffer, sizeof buffer, stdin);
  if ((token = strtok(buffer, " \t\r\n")) != NULL) {
    do {
      words[i] = token;
      i++;
    } 
    while ((token = strtok(NULL, " \t\r\n")) != NULL);
  }
  words[i] = NULL;

  if (strcmp(words[0], "cd") == 0) {
    if(chdir(words[1]) == -1) {
      perror("chdir error");
    }
  }

  if (strcmp("exit", words[0]) == 0) {
    exit(0);
  }

  int pid = fork();
  if (pid == 0) {
    execvp(words[0], words);
    perror("execvp error");
    exit(1);
  } else {
    wait(NULL);
  }
}