#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
  int file_descriptor;
  char buffer[2048];
  int bytes_read;

  if (argc < 2) {
    file_descriptor = 0;

    while((bytes_read = read(file_descriptor, buffer, sizeof(buffer))) > 0) {
      write(1, buffer, bytes_read);
    }
    close(file_descriptor);

  } else {
    for (int i = 1; i < argc; i++) {
      file_descriptor = open(argv[i], O_RDONLY);
      bytes_read = read(file_descriptor, buffer, sizeof(buffer));
      write(1, buffer, bytes_read);
      close(file_descriptor);
    }
  }

}