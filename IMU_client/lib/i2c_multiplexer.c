#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "i2c_multiplexer.h"

/* ------------------------------------------------------------ *
 * get_i2cbus_multiplexer() - Enables the I2C bus communication. Raspberry  *
 * Pi 2 uses i2c-1, RPI 1 used i2c-0, NanoPi also uses i2c-0.   *
 * ------------------------------------------------------------ */
void get_i2cbus_multiplexer(char *i2cbus, char *i2caddr) {

   if((i2cfd_ = open(i2cbus, O_RDWR)) < 0) {
      printf("Error failed to open I2C bus [%s].\n", i2cbus);
      exit(-1);
   }
   if(verbose_ == 1) printf("Debug: I2C bus device: [%s]\n", i2cbus);
   /* --------------------------------------------------------- *
    * Set I2C device (multiplexer I2C address is  0x70)      *
    * --------------------------------------------------------- */
   int addr = (int)strtol(i2caddr, NULL, 16);
   if(verbose_ == 1) printf("Debug: Sensor address: [0x%02X]\n", addr);

   if(ioctl(i2cfd_, I2C_SLAVE, addr) != 0) {
      printf("Error can't find sensor at address [0x%02X].\n", addr);
      exit(-1);
   }
}

int set_multiplexer(multiplexer_t channel)
{
   char reg = channel;
   write(i2cfd_, &reg, 1);
   return 0;
}