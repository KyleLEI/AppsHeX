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
char esp_msg[] = "XXESP8266 failed, retry";
char connecting_msg[] = "XXConnecting to base";
char locked_msg[] = "XXNEAR to unlock    ";

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
  int selection = 0;
  bool locked = true;
  int status[5] = // 0 1 2 for relay, 0 1 for rfid
	{
	    0 };

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
    {
      esp_msg[0] = 0;
      esp_msg[1] = 1;
      write (oledfd, esp_msg, sizeof(esp_msg));
      return -1;
    }
  printf ("ESP8266 Initialized\n");

  connecting_msg[0] = 0;
  connecting_msg[1] = 1;
  write (oledfd, connecting_msg, sizeof(connecting_msg));

  if (!smarthome_esp8266_connect (espfd))
    return -1;

  locked_msg[0] = 0;
  locked_msg[1] = 1;
  write (oledfd, locked_msg, sizeof(locked_msg));
  for (;;)
    {
      nbytes = read (apdsfd, (void *) &gest, sizeof(gest));
      if (nbytes == 1)
	{
	  if (!locked)
	    {
	      switch (gest)
		{
		case DIR_RIGHT:
		  selection--;
		  if (selection < 0)
		    selection = 4;
		  break;

		case DIR_LEFT:
		  selection++;
		  if (selection > 4)
		    selection = 0;
		  break;

		case DIR_UP:
		  if (selection != 4)
		    {
		      status[selection]++;
		      if (status[selection] > 2)
			{
			  status[selection] = 2;
			  continue;
			}
		      smarthome_esp8266_send_cmd (espfd, selection, status);
		    }
		  else
		    {
		      status[selection] = 1;
		      smarthome_esp8266_send_cmd (espfd, selection, status);
		      continue;
		    }

		  break;

		case DIR_DOWN:
		  if (selection != 4)
		    {
		      status[selection]--;
		      if (status[selection] < 0)
			{
			  status[selection] = 0;
			  continue;
			}
		      smarthome_esp8266_send_cmd (espfd, selection, status);
		    }
		  else
		    {
		      status[selection] = 0;
		      smarthome_esp8266_send_cmd (espfd, selection, status);
		      continue;
		    }
		  break;

		case DIR_FAR: // lock the controller
		  locked = true;
		  write (oledfd, locked_msg, sizeof(locked_msg));
		  smarthome_draw_hkust_logo (oledfd);
		  continue;
		  break;

		case DIR_NEAR:
		  continue;
		}
	      smarthome_update_oled (oledfd, selection, status);
	    }
	  else // controller locked
	    {
	      if (gest == DIR_NEAR) // only NEAR unlocks the device
		{
		  locked = false;
		  smarthome_update_oled (oledfd, selection, status);
		}
	    }
	}
    }

  return 0;
}
#endif
