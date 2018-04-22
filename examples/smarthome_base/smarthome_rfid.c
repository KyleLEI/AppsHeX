/*
 * smarthome_rfid.c
 *
 *  Created on: Apr 21, 2018
 *      Author: kyle
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <nuttx/contactless/mfrc522.h>
#include "smarthome_base.h"
/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef CONFIG_EXAMPLES_SMARTHOME_BASE_RFID_DEVNAME
#  define CONFIG_EXAMPLES_SMARTHOME_BASE_RFID_DEVNAME "/dev/rfid0"
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/
char access_granted_msg[] = "\n\nAccess Granted\nWelcome home!";
char access_denied_msg[] = "\n\nAccess Denied\n";
char reg_max_msg[] = "\n\nSorry no more\nnew cards allowed";
char reg_success_msg[] = "\n\nNew card is\nregistered";
char reg_abort_msg[] = "\n\nFailed to read\ncard";

/****************************************************************************
 * rfid_readuid_main
 ****************************************************************************/
int
smarthome_initialize_rfid (sh_state_t* sh_state)
{
  int* fdptr = &sh_state->rfidfd;

  *fdptr = open (CONFIG_EXAMPLES_SMARTHOME_BASE_RFID_DEVNAME, O_RDONLY);
  if (*fdptr < 0)
    {
      printf ("Failed to open %s\n",
      CONFIG_EXAMPLES_SMARTHOME_BASE_RFID_DEVNAME);
      return -1;
    }
  return 0;
}

void*
smarthome_rfid_daemon (void* args)
{
  int ret;
  int i;
  char buffer[10];
  sh_state_t* m_state = (sh_state_t*) args;
  int fd = m_state->rfidfd;
  bool* should_read = &m_state->should_read;

  if (fd < 0)
    {
      printf ("rfid_daemon: Illegal fd %d", fd);
      return NULL;
    }
  while (1)
    {
      if (*should_read)
	{
	  ret = read (fd, buffer, 11);
	  if (ret == 11)
	    {
	      printf ("rfid_daemon: RFID CARD UID = %s\n", buffer);
	      /* Loop through saved cards to see if this card is allowed */
	      for (i = 0; i < SH_NUM_REG_CARDS; i++)
		{
		  if (memcmp ((buffer + 2), m_state->cards[i], 8) == 0)
		    {
		      printf ("rfid_daemon: Access Granted!\n");
		      smarthome_write_slcd (m_state, access_granted_msg,
					    sizeof(access_granted_msg));
		      m_state->rgb_mode = sh_RGB_FLASH_GREEN;
		      usleep (1500000); /* Sleep to prevent reading again */
		      goto readnext;
		    }
		}

	      printf ("rfid_daemon: Access Denied!\n");
	      smarthome_write_slcd (m_state, access_denied_msg,
				    sizeof(access_denied_msg));
	      m_state->rgb_mode = sh_RGB_FLASH_RED;
	    }
	  else if (ret == -EAGAIN || ret == -EPERM)
	    {
	      printf ("rfid_daemon: Card is not present!\n");
	    }
	  else
	    {
	      printf ("rfid_daemon: Unknown error or same card\n");
	    }
	}

      /* Wait 500ms before trying again */
      readnext: usleep (500000);

    }
  return NULL;
}

int
smarthome_register_card (sh_state_t* sh_state)
{
  int ret;
  int i;
  int fd = sh_state->rfidfd;
  char buffer[10];

  sh_state->should_read = false;
  if (sh_state->card_count > SH_NUM_REG_CARDS)
    {
      smarthome_write_slcd (sh_state, reg_max_msg, sizeof(reg_max_msg));
      sh_state->should_read = true;
      return -1;
    }

  ret = read (fd, buffer, 11);
  if (ret == 11)
    {
      printf ("rfid_reg: RFID CARD UID = %s\n", buffer);
      memcpy (sh_state->cards[sh_state->card_count], buffer + 2, 8);
      sh_state->card_count++;
      smarthome_write_slcd (sh_state, reg_success_msg, sizeof(reg_success_msg));
      sh_state->should_read = true;
    }
  else
    {
      printf ("rfid_reg: Failed to read card\n");
      smarthome_write_slcd (sh_state, reg_abort_msg, sizeof(reg_abort_msg));
      sh_state->should_read = true;
      return -1;
    }

  return 0;
}

int
smarthome_read_cardid_from_flash (sh_state_t* sh_state)
{
  int fd;
  char buff[8];

  fd = open ("/mnt/userid.txt", O_RDONLY);
  if (fd < 0)
    return -1;

  while (read (fd, buff, 8))
    {
      printf ("rfid_flash_read: read ");
      fflush (stdout);
      write (1, buff, 8);
      printf (" from flash\n");

      memcpy (sh_state->cards[sh_state->card_count++], buff, 8);
    }

  printf ("Finished reading from flash, %d id read.\n", sh_state->card_count);
  close (fd);

  return 0;
}
