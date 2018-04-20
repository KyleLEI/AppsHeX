/*
 * smarthome_base.h
 *
 *  Created on: Apr 21, 2018
 *      Author: kyle
 */

#ifndef __EXAMPLES_SMARTHOME_BASE_SMARTHOME_BASE_H
#define __EXAMPLES_SMARTHOME_BASE_SMARTHOME_BASE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdbool.h>
#include <pthread.h>

/****************************************************************************
 * Public Types
 ****************************************************************************/

typedef enum
{
  sh_RGB_BREATH         = 0,
  sh_RGB_FLASH_RED 	    = 1,
  sh_RGB_FLASH_BLUE     = 2,
  sh_RGB_FLASH_GREEN    = 3
} sh_RGB_mode_t;



typedef struct
{
	pthread_t rgbled_thread;

	bool remote_connected;
	sh_RGB_mode_t rgb_mode;
} sh_state_t;

/**/



/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
int smarthome_rgbled_daemon(void*);



#endif /* __EXAMPLES_SMARTHOME_BASE_SMARTHOME_BASE_H */
