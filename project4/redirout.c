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
    }

    char *output_file = argv[1];
    
}