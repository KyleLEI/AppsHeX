/****************************************************************************
 * examples/smarthome_remote/smarthome_remote_main.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include <nuttx/sensors/apds9960.h>
#include "smarthome_remote.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define SH_MAIN "smarthome_remote_main: "

/****************************************************************************
 * Private Data
 ****************************************************************************/
char open_msg1[] = "XXELEC3300 Gp59";
char open_msg2[] = "XXPlease wait...";
char connecting_msg[] = "XXConnecting to base module";

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * smarthome_remote_main
 ****************************************************************************/
#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int
smarthome_remote_main (int argc, char *argv[])
{
  int oledfd;
  int apdsfd;

  //printf (SH_MAIN "Initializing OLED\n");
  oledfd = open ("/dev/slcd0", O_RDWR | O_NONBLOCK);
  if (oledfd < 0)
    {
      //int errcode = errno;
      //printf (SH_MAIN "ERROR: Failed to initialize OLED: %d\n", errcode);
      return -1;
    }
  //printf (SH_MAIN "OLED initialized\n");

  smarthome_clear_oled(oledfd);
  smarthome_draw_hkust_logo (oledfd);

  open_msg1[0]=0;
  open_msg1[1]=0;
  write (oledfd, open_msg1, sizeof(open_msg1));
  open_msg2[0]=0;
  open_msg2[1]=1;
  write (oledfd, open_msg2, sizeof(open_msg2));

  //printf (SH_MAIN "Initializing APDS-9960\n");
  apdsfd = open ("/dev/gest0", O_RDONLY | O_NONBLOCK);
  if (apdsfd < 0)
    {
      //int errcode = errno;
      //printf (SH_MAIN "ERROR: Failed to initialize APDS-9960: %d\n", errcode);
      return -1;
    }
  //printf (SH_MAIN "APDS-9960 initialized\n");

  //printf (SH_MAIN "Initializing ESP8266\n");
  //printf (SH_MAIN "ESP8266 initialized\n\n");

  connecting_msg[0]=0;
  connecting_msg[1]=1;
  write (oledfd, connecting_msg, sizeof(connecting_msg));


  return 0;
}
#endif
