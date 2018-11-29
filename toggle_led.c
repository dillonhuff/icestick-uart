#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/types.h>

#include <stdio.h>
#include <curses.h>

int main (int argc, char * const argv[]) {

  char FileOpenSTR[] ="/dev/cu.usbserial-14101";  

  int fd;
  fd = open(FileOpenSTR, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) {
    perror("open_port: Unable to open /dev/tty");
  }  

  printf("fd = %d\n", fd);

  struct termios options;
  tcgetattr(fd,&options);
  cfsetospeed(&options,B9600);
  options.c_cflag |=(CLOCAL | CREAD);
  tcsetattr(fd, TCSANOW, &options);

  int res = write(fd, "2", sizeof(char));

  printf("written = %d", res);

  close(fd);

  return 0; // End of the program
}
