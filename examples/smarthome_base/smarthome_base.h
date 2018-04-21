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
 * Pre-processor Definitions
 ****************************************************************************/
#define SH_NUM_RELAYS 4

/****************************************************************************
 * Public Types
 ****************************************************************************/

typedef enum
{
  sh_RGB_BREATH = 0,
  sh_RGB_FLASH_RED = 1,
  sh_RGB_FLASH_BLUE = 2,
  sh_RGB_FLASH_GREEN = 3
} sh_RGB_mode_t;

typedef struct
{
  /* RGBLED related */

  pthread_t rgbled_thread;
  sh_RGB_mode_t rgb_mode;

  /* GPIO(relay) related */

  int gpofd[SH_NUM_RELAYS];

  /* Wireless related */

  bool remote_connected;

} sh_state_t;

/**/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

void*
smarthome_rgbled_daemon (void* sh_state);

int smarthome_initialize_gpio(sh_state_t* sh_state);
int smarthome_write_gpio(sh_state_t* sh_state, int gpio_id, bool value);

#endif /* __EXAMPLES_SMARTHOME_BASE_SMARTHOME_BASE_H */
