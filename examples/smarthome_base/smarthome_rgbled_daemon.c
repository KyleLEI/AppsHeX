/****************************************************************************
 * examples/smarthome_base/smarthome_base_main.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/
/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

#include "smarthome_base.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_DEVNAME
#  define CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_DEVNAME "/dev/rgbled0"
#endif

#ifndef CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP
#  define CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP 5
#endif

#ifndef CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION
#  define CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION 250000
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/
void*
smarthome_rgbled_daemon (void* args)
{
  sh_RGB_mode_t * m_rgb_mode = &((sh_state_t*) args)->rgb_mode;
  int red = 255;
  int green = 0;
  int blue = 0;
  int sred = -CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
  int sgreen = CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
  int sblue = 0;
  int fd;
  char buffer[8];

  fd = open (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_DEVNAME, O_WRONLY);

  if (fd < 0)
    {
      printf ("Error opening %s!\n",
      CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_DEVNAME);
      return NULL;
    }

  while (1)
    {
      switch (*m_rgb_mode)
	{

	case sh_RGB_FLASH_RED:
	  red = 255;
	  green = 0;
	  blue = 0;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  red = 0;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  red = 255;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  red = 0;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  red = 255;
	  green = 0;
	  blue = 0;
	  sred = -CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	  sgreen = CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	  sblue = 0;

	  *m_rgb_mode = sh_RGB_BREATH;

	  break;
	case sh_RGB_FLASH_GREEN:
	  red = 0;
	  green = 255;
	  blue = 0;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  green = 0;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  green = 255;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  green = 0;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  red = 255;
	  green = 0;
	  blue = 0;
	  sred = -CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	  sgreen = CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	  sblue = 0;

	  *m_rgb_mode = sh_RGB_BREATH;

	  break;
	case sh_RGB_FLASH_BLUE:
	  red = 0;
	  green = 0;
	  blue = 255;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  blue = 0;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  blue = 255;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  blue = 0;
	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_FLASH_DURATION);

	  red = 255;
	  green = 0;
	  blue = 0;
	  sred = -CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	  sgreen = CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	  sblue = 0;

	  *m_rgb_mode = sh_RGB_BREATH;

	  break;

	default:
	case sh_RGB_BREATH:
	  red += sred;
	  green += sgreen;
	  blue += sblue;

	  if (green == 255)
	    {
	      sred = 0;
	      sgreen = -CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	      sblue = CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	    }

	  if (blue == 255)
	    {
	      sred = CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	      sgreen = 0;
	      sblue = -CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	    }

	  if (red == 255)
	    {
	      sred = -CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	      sblue = 0;
	      sgreen = CONFIG_EXAMPLES_SMARTHOME_BASE_RGBLED_STEP;
	    }

	  sprintf (buffer, "#%02X%02X%02X", red, green, blue);
	  (void) write (fd, buffer, 8);
	  usleep (5);
	  break;
	}
    }

  return NULL;
}
