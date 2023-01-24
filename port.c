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
    tty.c_cflag     &=  ~PARODD;

    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;

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
  //unsigned char msg[] = { 'O', 'U', 'T', 'O', 'N', ',', '1', '\r' };
  unsigned char msg[6] = "LON\r";
  write(serial_port, msg, sizeof(msg));

  char read_buf [256];
  memset(&read_buf, '\0', sizeof(read_buf));
  int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
  if (num_bytes < 0) {
      printf("Error reading: %s", strerror(errno));
      return 1;
  }

  printf("Read %i bytes. Received message: %s", num_bytes, read_buf);

  sleep(2);

  strcpy(msg, "LON\r");
  write(serial_port, msg, sizeof(msg));

  return 0;
}