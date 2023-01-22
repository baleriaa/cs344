#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])  {
  int file_descriptor =  open(argv[1], O_RDONLY);
  char buffer[2048];

  if (file_descriptor == -1) {
    perror("error opening file");
  }

  int bytes_read = read(file_descriptor, buffer, sizeof(buffer));
  if (bytes_read == -1) {
    perror("error reading file");
  }
  
  write(1, buffer, bytes_read);
  close(file_descriptor);

}