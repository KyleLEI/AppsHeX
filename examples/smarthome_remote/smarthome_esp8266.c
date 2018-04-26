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
 * Private Functions
 ****************************************************************************/
int
smarthome_esp8266_send_cmd (int espfd, char* cmd)
{
  int len;
  len = strlen (cmd);

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

bool
smarthome_esp8266_recv_ok (int espfd)
{
  char buffer[16];
  int ret;

  ret = read (espfd, buffer, sizeof(buffer)); // probably need debugging here

  if (ret < 2)
    return false ;

  if (memcmp (buffer, "OK", 2) == 0)
    return true ;

  return false ;
}
/****************************************************************************
 * Public Functions
 ****************************************************************************/
bool
smarthome_esp8266_init (int espfd)
{
  smarthome_esp8266_send_cmd (espfd,"ATE0\r\n");
  //smarthome_esp8266_flush (espfd);
  return smarthome_esp8266_recv_ok (espfd);
}
