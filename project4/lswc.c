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
    (void) argc;
    int pfd[2];
    pipe(pfd);
    pid_t process_id = fork();

    if (process_id == 0) { // child
        dup2(pfd[0], STDIN_FILENO); // read end of pipe into stdin
        close(pfd[1]);
        execlp("wc", "wc", "-l", NULL);
    } else {    // parent
        dup2(pfd[1], STDOUT_FILENO); // write end of pipe into stdout
        close(pfd[0]);
        if (argc > 1) {
            execlp("ls", "ls", "-1a", argv[1], NULL);
        } else if (argc == 1) {
            execlp("ls", "ls", "-1a", NULL);
        }
    }
}