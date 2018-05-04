/****************************************************************************
 * examples/smarthome_base/smarthome_adc.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/
/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

#include <nuttx/analog/adc.h>
#include <nuttx/analog/ioctl.h>
#include "smarthome_base.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#ifndef CONFIG_EXAMPLES_SMARTHOME_BASE_ADC_DEVNAME
#  define CONFIG_EXAMPLES_SMARTHOME_BASE_ADC_DEVNAME "/dev/adc0"
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void*
smarthome_adc_daemon (void* args)
{
  bool * m_is_auto = ((sh_state_t*) args)->is_auto;
  struct adc_msg_s sample;

  int fd;
  int ret;

  fd = open (CONFIG_EXAMPLES_SMARTHOME_BASE_ADC_DEVNAME, O_RDONLY);

  if (fd < 0)
    {
      printf ("Error opening %s!\n",
      CONFIG_EXAMPLES_SMARTHOME_BASE_ADC_DEVNAME);
      return NULL;
    }

  while (1)
    {
      /* Trigger ADC conversion */

      ret = ioctl (fd, ANIOC_TRIGGER, 0);
      if (ret < 0)
	{
	  printf ("adc_daemon: ANIOC_TRIGGER ioctl failed\n");
	}

      /* Read ADC */

      ret = read (fd, &sample, sizeof(struct adc_msg_s));
      if (ret < 0)
	{
	  printf ("adc_daemon: ADC read failed\n");
	}
      else if (ret == 0)
	{
	  printf ("adc_daemon: No data\n");
	}
      else
	{
	  printf ("adc_daemon: channel: %d value: %d\n", sample.am_channel,
		  sample.am_data); //TODO: automate here
	}
      usleep (250000); // wait 250ms
    }
  return NULL;
}
