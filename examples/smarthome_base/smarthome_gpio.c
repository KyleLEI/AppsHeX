/****************************************************************************
 * examples/smarthome_base/smarthome_gpio.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/
/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

#include "smarthome_base.h"
#include <nuttx/ioexpander/gpio.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#ifndef CONFIG_EXAMPLES_SMARTHOME_BASE_GPIO_DEVNAME
#  define CONFIG_EXAMPLES_SMARTHOME_BASE_GPIO_DEVNAME "/dev/gpout%d"
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int
smarthome_initialize_gpio (sh_state_t* sh_state)
{
  char devpath[16];
  int i;
  int* fds = sh_state->gpofd;

  /* Open GPIO drivers */
  for (i = 0; i < SH_NUM_RELAYS; i++)
    {
      sprintf (devpath, CONFIG_EXAMPLES_SMARTHOME_BASE_GPIO_DEVNAME, i);
      printf ("Opening GPIO Driver: %s\n", devpath);

      fds[i] = open (devpath, O_RDWR);
      if (fds[i] < 0)
	{
	  int errcode = errno;
	  fprintf (stderr, "ERROR: Failed to open %s: %d\n", devpath, errcode);
	  return -1;
	  break;
	}
    }

  return 0;
}

int
smarthome_write_gpio (sh_state_t* sh_state, int gpio_id, bool value)
{
  int ret;
  int* fds = sh_state->gpofd;
  bool invalue;
  int fd = fds[gpio_id];

  if (fd < 0)
    {
      printf ("Illegal fd: %d\n", fd);
      return -1;
    }

  printf ("  Writing:       Value=%u\n", (unsigned int) value);
  ret = ioctl (fd, GPIOC_WRITE, (unsigned long) value);
  if (ret < 0)
    {
      int errcode = errno;
      fprintf (stderr, "ERROR: Failed to write value %u to fd %d: %d\n",
	       (unsigned int) value, fd, errcode);
      return -1;
    }

  /* Re-read the pin value */

  ret = ioctl (fd, GPIOC_READ, (unsigned long) ((uintptr_t) &invalue));
  if (ret < 0)
    {
      int errcode = errno;
      fprintf (stderr, "ERROR: Failed to re-read value from fd %d: %d\n", fd,
	       errcode);
      return -1;
    }

  printf ("  Verify:        Value=%u\n", (unsigned int) invalue);

  return 0;
}
