/****************************************************************************
 * examples/mpu6050/mpu6050_main.c
 *
 *   Author: Kyle Lei <leizhao2@gmail.com>
 *   Reference: apds9960/apds9960_main.c
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <nuttx/sensors/mpu6050.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef CONFIG_EXAMPLES_MPU6050_DEVNAME
#  define CONFIG_EXAMPLES_MPU6050_DEVNAME "/dev/mpu6050"
#endif

#ifndef MPU6050_ONE_G
#define MPU6050_ONE_G					9.80665f
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * mpu6050_main
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int mpu6050_main(int argc, char *argv[])
#endif
{
  int fd;
  int nbytes;
  uint8_t tempBuffer[12];
  float buffer[6];

  fd = open(CONFIG_EXAMPLES_MPU6050_DEVNAME, O_RDONLY|O_NONBLOCK);
  if (fd < 0)
    {
      int errcode = errno;
      printf("ERROR: Failed to open %s: %d\n",
             CONFIG_EXAMPLES_MPU6050_DEVNAME, errcode);
      goto errout;
    }

  int count;
  for(count=5;count>0;count--)
    {
      nbytes = read(fd, (void *)tempBuffer, sizeof(tempBuffer));

      if (nbytes == 12){
    	  	  for(int i=0;i<3;i++){
    	  		  /* Concatenate H and L bits */
    	  		  buffer[i]=((int16_t) ((uint16_t) tempBuffer[2 * i] << 8) +
    	  				  tempBuffer[2 * i + 1]);
    	  		  /* Convert to m/(s*s) */
    	  		  buffer[i]=buffer[i]/32767*2*MPU6050_ONE_G;
    	  	  }
    	  	for(int i=3;i<6;i++){
    	  	    	  /* Concatenate H and L bits */
    	  	    	  buffer[i]=((int16_t) ((uint16_t) tempBuffer[2 * i] << 8) +
    	  	    	  				  tempBuffer[2 * i + 1]);
    	  	}
    	  	printf("ACCEL_X = %.5f\n",buffer[0]);
    	  	printf("ACCEL_Y = %.5f\n",buffer[1]);
    	  	printf("ACCEL_Z = %.5f\n",buffer[2]);
    	  	printf("GYRO_X = %f\n",buffer[3]);
    	  	printf("GYRO_Y = %f\n",buffer[4]);
    	  	printf("GYRO_Z = %f\n\n",buffer[5]);

      }


      fflush(stdout);

      /* Wait 1s */

      sleep(1);
    }
  close(fd);
  return 0;

errout:
  return EXIT_FAILURE;
}
