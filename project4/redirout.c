// Parse the command line to make sure the user has entered the minimum amount of information.
// open() the output file.
// Create a pipe().
// fork() a child process to run the command.
// In the child:
// dup2() the output end of the pipe into stdout.
// close() the input end of the pipe.
// execvp() the command.
// In the parent:
// close() the output end of the pipe.
// Repeatedly read() from the input end into a buffer.
// write() the buffer into the output file you opened earlier.
// read() will return zero bytes read on end-of-file (EOF).
// close() the input end of the pipe.
// close() the output file.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Missing arguments. Be sure to follow the format: redirout  outfilename  command opt1 opt2 ...\n");
        exit(1);
    }

    char *output_file = argv[1];

    int fd = open(output_file, O_CREAT | O_WRONLY, 0644);
    int pfd[2];
    pipe(pfd);
    pid_t process_id = fork();
    if (process_id == 0) {
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[0]);
        execvp(argv[2], argv + 2);
        perror("execvp error");
        exit(1);
    } else {
        close(pfd[1]);
        char buffer[1024];
        int bytes_read;
        while ((bytes_read = read(pfd[0], buffer, 1024)) > 0) {
            write(fd, buffer, bytes_read);
        }
        close(pfd[0]);
        close(fd);
    }
}

