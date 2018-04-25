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

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

void smarthome_clear_oled(int oledfd);
void smarthome_draw_hkust_logo(int oledfd);

#endif /* __EXAMPLES_SMARTHOME_REMOTE_SMARTHOME_REMOTE_H */
