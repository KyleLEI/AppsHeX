/****************************************************************************
 * examples/smarthome_base/smarthome_lcd.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/
/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/ioctl.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "smarthome_base.h"
#include <nuttx/lcd/slcd_ioctl.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#ifndef CONFIG_EXAMPLES_SMARTHOME_BASE_SLCD_DEVNAME
#  define CONFIG_EXAMPLES_SMARTHOME_BASE_SLCD_DEVNAME "/dev/slcd0"
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int
smarthome_initialize_slcd (sh_state_t* sh_state)
{
  int* fdptr = &sh_state->slcdfd; //manual pass by reference

  /* Open SLCD driver */
  printf ("Opening GPIO Driver: %s\n",
  CONFIG_EXAMPLES_SMARTHOME_BASE_SLCD_DEVNAME);

  *fdptr = open (CONFIG_EXAMPLES_SMARTHOME_BASE_SLCD_DEVNAME, O_RDWR);
  if (*fdptr < 0)
    {
      int errcode = errno;
      fprintf (stderr, "ERROR: Failed to open %s: %d\n",
      CONFIG_EXAMPLES_SMARTHOME_BASE_SLCD_DEVNAME,
	       errcode);
      return -1;
    }

  char initMsg[]="ELEC3300 Gp59\nPlease wait...";
  write(*fdptr,initMsg,sizeof(initMsg)-1);

  return 0;
}

int smarthome_write_slcd(sh_state_t* sh_state, char* str, size_t strlen){
  return  write(sh_state->slcdfd,str,strlen-1);
}
