/****************************************************************************
 * examples/smarthome_remote/smarthome_esp8266.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/
/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>

#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "smarthome_remote.h"

/****************************************************************************
 * Private Data
 ****************************************************************************/
char AT_RST[]="AT+RST\r\n";
char ATE0[]="ATE0\r\n";

/****************************************************************************
 * Private Functions
 ****************************************************************************/
int
smarthome_esp8266_send_cmd (int espfd, char* cmd)
{
  int len;
  len = strlen (cmd) + 1; //send '\0' as well

  return write (espfd, cmd, len);
}

void
smarthome_esp8266_flush (int espfd)
{
  char buffer[16];
  ssize_t ret;

  do
    {
      ret = read (espfd, buffer, sizeof(buffer));
    }
  while (ret > 0);
  //discard everything read
}

/* Process "\r\nOK\r\n" */
bool
smarthome_esp8266_recv_ok (int espfd)
{
  char buff[16];
  int ret;

  ret = read (espfd, buff, sizeof(buff));

  if (strstr (buff, "OK") != NULL)
    return true ;

  return false ;
}
/****************************************************************************
 * Public Functions
 ****************************************************************************/
bool
smarthome_esp8266_init (int espfd)
{
  write (espfd, AT_RST, sizeof(AT_RST));
  sleep(1);
  smarthome_esp8266_flush (espfd);

  write (espfd, ATE0, sizeof(ATE0));
  usleep (100000);
  return smarthome_esp8266_recv_ok (espfd);
}
