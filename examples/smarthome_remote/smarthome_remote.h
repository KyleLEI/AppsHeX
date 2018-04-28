/*
 * smarthome_remote.h
 *
 *  Created on: Apr 25, 2018
 *      Author: kyle
 */

#ifndef __EXAMPLES_SMARTHOME_REMOTE_SMARTHOME_REMOTE_H
#define __EXAMPLES_SMARTHOME_REMOTE_SMARTHOME_REMOTE_H 1

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdbool.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/* OLED-related */
void
smarthome_clear_oled (int oledfd);
void
smarthome_draw_hkust_logo (int oledfd);
void
smarthome_draw_light_on (int oledfd);
void
smarthome_draw_light_off (int oledfd);
void
smarthome_draw_rfid (int oledfd);

/* ESP8266-related */
bool
smarthome_esp8266_init (int espfd);
bool
smarthome_esp8266_connect (int espfd);
bool
smarthome_esp8266_send (int espfd,char* cmd, int len);

#endif /* __EXAMPLES_SMARTHOME_REMOTE_SMARTHOME_REMOTE_H */
