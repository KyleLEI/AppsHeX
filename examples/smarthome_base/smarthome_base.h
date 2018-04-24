/*
 * smarthome_base.h
 *
 *  Created on: Apr 21, 2018
 *      Author: kyle
 */

#ifndef __EXAMPLES_SMARTHOME_BASE_SMARTHOME_BASE_H
#define __EXAMPLES_SMARTHOME_BASE_SMARTHOME_BASE_H 1

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
#define SH_NUM_REG_CARDS 8

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

typedef enum
{
  sh_RFID_IDLE = 0,
  sh_RFID_READ = 1,
  sh_RFID_REG_CARD = 2,
  sh_RFID_DEL_CARDS = 3
} sh_RFID_mode_t;

typedef struct
{
  /* RGBLED related */

  pthread_t rgbled_thread;
  sh_RGB_mode_t rgb_mode;

  /* GPIO(relay) related */

  int gpofd[SH_NUM_RELAYS];

  /* SLCD related */

  int slcdfd;

  /* RFID related */

  pthread_t rfid_thread;
  int rfidfd;
  sh_RFID_mode_t rfid_mode;
  char cards[SH_NUM_REG_CARDS][8];
  int card_count;

  /* Wireless related */

  bool remote_connected;

} sh_state_t;

/**/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

void*
smarthome_rgbled_daemon (void* sh_state);
void*
smarthome_rfid_daemon (void* sh_state);

int
smarthome_initialize_gpio (sh_state_t* sh_state);
int
smarthome_write_gpio (sh_state_t* sh_state, int gpio_id, bool value);

int
smarthome_initialize_slcd (sh_state_t* sh_state);
int
smarthome_write_slcd (sh_state_t* sh_state, char* str, size_t strlen);

int
smarthome_initialize_rfid (sh_state_t* sh_state);
int
smarthome_read_cardid_from_flash (sh_state_t* sh_state);

#endif /* __EXAMPLES_SMARTHOME_BASE_SMARTHOME_BASE_H */
