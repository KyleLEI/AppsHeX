/****************************************************************************
 * examples/smarthome_remote/smarthome_oled.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/
/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>

#include <sys/ioctl.h>

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

/****************************************************************************
 * Public Functions
 ****************************************************************************/
void
smarthome_clear_oled (int oledfd)
{
  ioctl (oledfd, SLCDIOC_CLEAR, 0);
}

void
smarthome_draw_hkust_logo (int oledfd)
{
  bmp.x0 = OLED_MID - 15;
  bmp.x1 = OLED_MID + 15;
  bmp.bmp = hkust_logo;
  ioctl (oledfd, SLCDIOC_DRAWBMP, (unsigned long) &bmp);
}
