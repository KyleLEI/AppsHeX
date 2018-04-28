/****************************************************************************
 * examples/smarthome_remote/smarthome_remote_main.c
 *
 *   Author: Kyle Lei <leizhao2@gmail.com>
 *
 * I'm removing debug messages to save the precious memory on STM32F103C8
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

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
char connecting_msg[] = "XXConnecting to base";
char connected_msg[] = "XXConnected to base";
char GPIO0_0[] = "GPIO_RESET0";
char GPIO0_1[] = "GPIO_SET0";

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
  int espfd;

  int nbytes;
  char gest;

  /* Open OLED driver*/
  oledfd = open ("/dev/slcd0", O_RDWR | O_NONBLOCK);
  if (oledfd < 0)
    return -1;

  smarthome_clear_oled (oledfd);
  smarthome_draw_hkust_logo (oledfd);

  open_msg1[0] = 0;
  open_msg1[1] = 0;
  write (oledfd, open_msg1, sizeof(open_msg1));
  open_msg2[0] = 0;
  open_msg2[1] = 1;
  write (oledfd, open_msg2, sizeof(open_msg2));

  /* Open APDS-9960 driver */
  apdsfd = open ("/dev/gest0", O_RDONLY | O_NONBLOCK);
  if (apdsfd < 0)
    return -1;

  /* Open ESP8266 USART(tty) driver */
  espfd = open ("/dev/ttyS1", O_RDWR | O_NONBLOCK);
  if (espfd < 1)
    return -1;

  if (!smarthome_esp8266_init (espfd))
    return -1;
  printf ("ESP8266 Initialized\n");

  connecting_msg[0] = 0;
  connecting_msg[1] = 1;
  write (oledfd, connecting_msg, sizeof(connecting_msg));

  if (!smarthome_esp8266_connect (espfd))
    return -1;

  connected_msg[0] = 0;
  connected_msg[1] = 1;
  write (oledfd, connected_msg, sizeof(connected_msg));
  for (;;)
    {
      nbytes = read (apdsfd, (void *) &gest, sizeof(gest));
      if (nbytes == 1)
	{
	  switch (gest)
	    {
	    case DIR_LEFT:
	      smarthome_draw_hkust_logo (oledfd);
	      break;

	    case DIR_RIGHT:
	      smarthome_draw_rfid (oledfd);
	      break;

	    case DIR_UP:
	      smarthome_esp8266_send (espfd, GPIO0_0, sizeof(GPIO0_0));
	      smarthome_draw_light_on (oledfd);
	      break;

	    case DIR_DOWN:
	      smarthome_esp8266_send (espfd, GPIO0_1, sizeof(GPIO0_1));
	      smarthome_draw_light_off (oledfd);
	      break;
	    }
	}
    }

  return 0;
}
#endif
