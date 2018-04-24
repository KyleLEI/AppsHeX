/****************************************************************************
 * examples/ssd1306_seg/ssd1306_seg_main.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <nuttx/lcd/ssd1306_seg.h>
#include "ssd1306_img.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef EXAMPLES_SSD1306_SEG_DEVNAME
#  define EXAMPLES_SSD1306_SEG_DEVNAME "/dev/slcd0"
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * hello_main
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int
ssd1306_seg_main (int argc, char *argv[])
#endif
{
  int fd;
  int ret;
  char buffer[32];

  /* Open the SSD1306 alphanumeric driver */
  fd = open (EXAMPLES_SSD1306_SEG_DEVNAME, O_RDWR | O_NONBLOCK);
  if (fd < 0)
    {
      int errcode = errno;
      printf ("ERROR: Failed to open %s: %d\n",
      EXAMPLES_SSD1306_SEG_DEVNAME,
	      errcode);
      goto errout;
    }

  /* Clear the screen */
  ret = ioctl (fd, SLCDIOC_CLEAR, 0);

  if (ret < 0)
    {
      int errcode = errno;
      printf ("ssd1306_seg: ERROR: ioctl(SLCDIOC_CLEAR) failed: %d\n", errcode);
      goto errout;
    }

  sprintf (buffer, "\x01\x01Hello from main!");

  ret = write (fd, buffer, sizeof(buffer));

  if (ret < 0)
    {
      int errcode = errno;
      printf ("ssd1306_seg: ERROR: write failed: %d\n", errcode);
      goto errout;
    }

  struct slcd_bmp_s bmp;
  bmp.y0 = 2;
  bmp.y1 = 8;

  while (1)
    {
      bmp.x0 = 63 - 15;
      bmp.x1 = 63 + 15;
      bmp.bmp = hkust_logo;

      ioctl (fd, SLCDIOC_CLEAR, 0);
      ioctl (fd, SLCDIOC_DRAWBMP, (unsigned long) &bmp);

      sleep (1);

      bmp.x0 = 63 - 14;
      bmp.x1 = 63 + 15;
      bmp.bmp = light_off;
      ioctl (fd, SLCDIOC_CLEAR, 0);
      ioctl (fd, SLCDIOC_DRAWBMP, (unsigned long) &bmp);
      sleep (1);

      bmp.x0 = 63 - 20;
      bmp.x1 = 63 + 21;
      bmp.bmp = light_on;
      ioctl (fd, SLCDIOC_CLEAR, 0);
      ioctl (fd, SLCDIOC_DRAWBMP, (unsigned long) &bmp);
      sleep (1);

      bmp.x0 = 63 - 40;
      bmp.x1 = 63 + 40;
      bmp.bmp = rfid;
      ioctl (fd, SLCDIOC_CLEAR, 0);
      ioctl (fd, SLCDIOC_DRAWBMP, (unsigned long) &bmp);
      sleep (1);

    }

  return 0;
  errout: return EXIT_FAILURE;

}
