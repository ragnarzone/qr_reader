#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <thread>
#include <iostream>

// Linux headers
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

void read_timeout(int timeout, int serial_port)
{
  sleep(timeout);
  system("echo \"LOFF\" > /dev/ttyUSB0");
  system("echo \"LOFF\" > /dev/ttyUSB0");
}

int main() {

  int timeout = 3;   // timeout after which camera stops reading

  // Open the serial port. 
  int serial_port = open("/dev/ttyUSB0", O_RDWR);

  // start timeout thread
  thread th1(read_timeout, timeout, serial_port);

  // Create new termios struct
  struct termios tty;

  // Read in existing settings, and handle any error
  if(tcgetattr(serial_port, &tty) != 0) {
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      return 1;
  }

    //tty.c_cc[VTIME] = 30;    // Wait
    //tty.c_cc[VMIN] = 0;

    tty.c_cflag     |=  PARENB;
    tty.c_cflag     &=  ~PARODD;

    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;

    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_lflag |= ICANON;       // canonical


  cfsetispeed(&tty, B115200);
  cfsetospeed(&tty, B115200);

  // Save tty settings, also checking for error
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      return 1;
  }

    //----------------------------------------------//

  // Write to serial port
  unsigned char msg[] = "LON\r";
  write(serial_port, msg, sizeof(msg));
  
  // Create buffer
  char read_buf [256];
  memset(&read_buf, '\0', sizeof(read_buf));

  // Read into buffer from port
  int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

  // Output error message if reading not successfull
  if (num_bytes < 0) {
      printf("Error reading: %s", strerror(errno));
      return 1;
  }
  
  // Output message
  printf("Read %i bytes. Received message: %s", num_bytes, read_buf);

  return 0;
}