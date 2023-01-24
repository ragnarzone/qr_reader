#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h> 

int main() {
  // Open the serial port. 
  int serial_port = open("/dev/ttyUSB0", O_RDWR);

  // Create new termios struct
  struct termios tty;

  // Read in existing settings, and handle any error
  if(tcgetattr(serial_port, &tty) != 0) {
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      return 1;
  }

    tty.c_cflag     |=  PARENB;
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;

    tty.c_cc[VMIN]   =  1;                  // read doesn't block
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

  
  cfsetispeed(&tty, B115200);
  cfsetospeed(&tty, B115200);

  // Save tty settings, also checking for error
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      return 1;
  }

  // Write to serial port
  //unsigned char msg[4] = "LON\r";
  //write(serial_port, msg, sizeof(msg));

  /* Write into port */
    unsigned char cmd[] = "LON\r";
    int n_written = 0;
    int spot = 0;

    do {
        n_written = write( serial_port, &cmd[spot], 1 );
        spot += n_written;
    } while (cmd[spot-1] != '\r' && n_written > 0);

  return 0;
}