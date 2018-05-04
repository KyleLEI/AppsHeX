/****************************************************************************
 * examples/smarthome_remote/smarthome_oled.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/
/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

#include <nuttx/lcd/ssd1306_seg.h>
#include "smarthome_remote.h"
#include "smarthome_img.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define OLED_MID 63

/****************************************************************************
 * Private Data
 ****************************************************************************/

struct slcd_bmp_s bmp =
  {
      .y0 = 2,
      .y1 = 8 };

struct slcd_fill_s fill =
  {
      .start_line = 2,
      .end_line = 7,
      .color = 0x00 };

char rfid_msg[] = "XXReg new/del all   ";

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void
smarthome_clear_img (int oledfd)
{
  ioctl (oledfd, SLCDIOC_FILLLINE, (unsigned long) &fill);
}

void
smarthome_clear_oled (int oledfd)
{
  ioctl (oledfd, SLCDIOC_CLEAR, 0);
}

void
smarthome_draw_hkust_logo (int oledfd)
{
  smarthome_clear_img (oledfd);
  bmp.x0 = OLED_MID - 15;
  bmp.x1 = OLED_MID + 15;
  bmp.bmp = hkust_logo;
  ioctl (oledfd, SLCDIOC_DRAWBMP, (unsigned long) &bmp);
}

void
smarthome_draw_light_off (int oledfd)
{
  smarthome_clear_img (oledfd);
  bmp.x0 = OLED_MID - 14;
  bmp.x1 = OLED_MID + 15;
  bmp.bmp = light_off;
  ioctl (oledfd, SLCDIOC_DRAWBMP, (unsigned long) &bmp);
}

void
smarthome_draw_light_on (int oledfd)
{
  smarthome_clear_img (oledfd);
  bmp.x0 = OLED_MID - 20;
  bmp.x1 = OLED_MID + 21;
  bmp.bmp = light_on;
  ioctl (oledfd, SLCDIOC_DRAWBMP, (unsigned long) &bmp);
}

void
smarthome_draw_rfid (int oledfd)
{
  smarthome_clear_img (oledfd);
  bmp.x0 = OLED_MID - 40;
  bmp.x1 = OLED_MID + 40;
  bmp.bmp = rfid;
  ioctl (oledfd, SLCDIOC_DRAWBMP, (unsigned long) &bmp);
}

void
smarthome_update_oled (int oledfd, int selection, int status[])
{
  char buff[32];
  int bytelen;

  if (selection <= 3) // relay commands
    {
      switch (status[selection])
	{
	case 0:
	  bytelen = sprintf (buff, "XXLight %d: off       ", selection + 1);

	  buff[0] = 0;
	  buff[1] = 1;

	  write (oledfd, buff, bytelen + 1);
	  smarthome_draw_light_off (oledfd);
	  break;
	case 1:
	  bytelen = sprintf (buff, "XXLight %d: auto     ", selection + 1);

	  buff[0] = 0;
	  buff[1] = 1;

	  write (oledfd, buff, bytelen + 1);
	  smarthome_draw_light_on (oledfd); //TODO: new icon
	  break;
	case 2:
	  bytelen = sprintf (buff, "XXLight %d: on       ", selection + 1);

	  buff[0] = 0;
	  buff[1] = 1;

	  write (oledfd, buff, bytelen + 1);
	  smarthome_draw_light_on (oledfd);
	  break;
	}
    }
  else // rfid command
    {
      rfid_msg[0] = 0;
      rfid_msg[1] = 1;

      write (oledfd, rfid_msg, sizeof(rfid_msg));
      smarthome_draw_rfid (oledfd);
    }
}
