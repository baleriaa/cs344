// Parse the command line
// Make a pipe() in the parent
// fork().
// The child will run wc:
// dup2() the read end of the pipe into stdin
// close() the write end of the pipe
// execlp() the wc command
// The parent will run ls:
// dup2() the write end of the pipe into stdout
// close() the read end of the pipe
// execlp() the ls command

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pfd[2];
    int process_id = fork();

    pipe(pfd);

    if (process_id == 0) {
        // Child process
    } else {
        // Parent process
    }

}