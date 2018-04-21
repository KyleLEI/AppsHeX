/****************************************************************************
 * examples/smarthome_base/smarthome_base_main.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include <netutils/esp8266.h>

#include "smarthome_base.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define SH_MAIN "smarthome_base_main: "

/****************************************************************************
 * Private Data
 ****************************************************************************/
sh_state_t g_sh_state =
  {
      .rgb_mode = sh_RGB_BREATH,

      .gpofd =
	{
	    -1 },

      .slcdfd = -1,

      .rfidfd = -1,
      .should_read = false,
      .cards =
	{
	    "04718E00" },
      .card_count = 1,

      .remote_connected = false };

char waiting_msg[] = "\n\nWaiting for\nremote module...";
char conn_msg[] = "\n\nRemote module\nconnected";
char disconn_msg[] = "\n\nRemote module\ndisconnected";
/****************************************************************************
 * Private Functions
 ****************************************************************************/
void
connectedCB (int socket)
{
  printf ("!!! %d Connected !!!\n", socket);
  g_sh_state.remote_connected = true;
  g_sh_state.rgb_mode = sh_RGB_FLASH_BLUE;
  smarthome_write_slcd (&g_sh_state, conn_msg, sizeof(conn_msg));
}

void
disconnectCB (int socket)
{
  printf ("!!! %d Disconnected !!!\n", socket);
  g_sh_state.remote_connected = false;
  g_sh_state.rgb_mode = sh_RGB_FLASH_RED;
  smarthome_write_slcd (&g_sh_state, disconn_msg, sizeof(disconn_msg));
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * smarthome_base_main
 ****************************************************************************/
#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int
smarthome_base_main (int argc, char *argv[])
#endif
{
  int ret;
  int gpio_id;
  struct sockaddr_in serv_addr;
  char buff[128] =
    {
	0 };
  ssize_t rsize = 0;

  printf (SH_MAIN "Initializing SLCD\n");
  ret = smarthome_initialize_slcd (&g_sh_state);
  if (ret < 0)
    {
      printf (SH_MAIN "ERROR initializing SLCD\n");
      return 1;
    }
  printf (SH_MAIN "SLCD initialized\n\n");

  printf (SH_MAIN "Spawning rgbled_daemon\n");
  pthread_create (&g_sh_state.rgbled_thread, NULL, smarthome_rgbled_daemon,
		  (void*) &g_sh_state);
  printf (SH_MAIN "rgbled_daemon spawned\n\n");

  printf (SH_MAIN "Initializing GPIO\n");
  ret = smarthome_initialize_gpio (&g_sh_state);
  if (ret < 0)
    {
      printf (SH_MAIN "ERROR initializing GPIO\n");
      return 1;
    }
  printf (SH_MAIN "GPIO initialized\n\n");

  printf (SH_MAIN "Initializing RFID\n");
  ret = smarthome_initialize_rfid (&g_sh_state);
  if (ret < 0)
    {
      printf (SH_MAIN "ERROR initializing RFID\n");
      return 1;
    }
  printf (SH_MAIN "RFID initialized\n\n");

  printf (SH_MAIN "Spawning RFID daemon\n");
  pthread_create (&g_sh_state.rfid_thread, NULL, smarthome_rfid_daemon,
		  (void*) &g_sh_state);
  printf (SH_MAIN "RFID daemon spawned\n\n");

  printf (SH_MAIN "Initializing ESP8266\n");
  lesp_initialize (); /* ESP8266 worker thread spawned inside */
  lesp_soft_reset ();
  printf (SH_MAIN "ESP8266 initialized\n\n");

  int sockfd = lesp_socket (PF_INET, SOCK_STREAM, 0);

  serv_addr.sin_family = PF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons (233);

  lesp_bindlistenaccept (sockfd, (struct sockaddr *) &serv_addr,
			 sizeof(serv_addr), connectedCB, disconnectCB);

  smarthome_write_slcd (&g_sh_state, waiting_msg, sizeof(waiting_msg));
  g_sh_state.rgb_mode = sh_RGB_FLASH_GREEN;
  g_sh_state.should_read = true;/* start reading RFID*/

  do
    {
      if (!g_sh_state.remote_connected || rsize < 0)
	sleep (1);
      rsize = lesp_recv (sockfd, (uint8_t *) buff, sizeof(buff), 0); //returns -1 if waited too long
      if (rsize > 0)
	{
	  printf ("Received %d bytes: ", rsize);
	  fflush (stdout);
	  write (1, buff, rsize);
	  puts ("\n");
	  fflush (stdout);
	  if (memcmp (buff, "GPIO_SET", 8) == 0)
	    {
	      g_sh_state.rgb_mode = sh_RGB_FLASH_BLUE;
	      gpio_id = buff[8] - '0';
	      printf ("Setting GPIO %d\n", gpio_id);
	      ret = smarthome_write_gpio (&g_sh_state, gpio_id, true);
	      if (ret < 0)
		printf (SH_MAIN "Failed to write gpio %d\n", gpio_id);

	    }
	  else if (memcmp (buff, "GPIO_RESET", 10) == 0)
	    {
	      g_sh_state.rgb_mode = sh_RGB_FLASH_BLUE;
	      gpio_id = buff[10] - '0';
	      printf ("Resetting GPIO %d\n", gpio_id);
	      ret = smarthome_write_gpio (&g_sh_state, gpio_id, false);
	      if (ret < 0)
		printf (SH_MAIN "Failed to write gpio %d\n", gpio_id);
	    }
	  else if (memcmp (buff, "REG_CARD", 8) == 0)
	    {
	      g_sh_state.rgb_mode = sh_RGB_FLASH_BLUE;
	      printf ("Registering new card\n");
	      ret = smarthome_register_card (&g_sh_state);
	      if (ret < 0)
		printf (SH_MAIN "Failed to register new card\n");
	    }
	  printf ("\n");
	}
    }
  while (1);

  return 0;
}
