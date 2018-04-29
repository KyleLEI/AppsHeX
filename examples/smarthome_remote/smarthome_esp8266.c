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
#include <stdio.h>

#include "smarthome_remote.h"

/****************************************************************************
 * Private Data
 ****************************************************************************/
char AT_RST[] = "AT+RST\r\n";
char ATE0[] = "ATE0\r\n";
char AT_CIPSTART[] = "AT+CIPSTART=\"TCP\",\"192.168.4.1\",233\r\n";
char CARD_REG[] = "CARD_REG";
char CARD_DEL[] = "CARD_DEL";

/****************************************************************************
 * Private Functions
 ****************************************************************************/
//int
//smarthome_esp8266_send_cmd (int espfd, char* cmd)
//{
//  int len;
//  len = strlen (cmd) + 1; //send '\0' as well
//
//  return write (espfd, cmd, len);
//}
void
smarthome_esp8266_flush (int espfd)
{
  char buffer[32];
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
  char buff[32];

  read (espfd, buff, sizeof(buff));

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
  usleep (500000);
  write (espfd, AT_RST, sizeof(AT_RST));
  sleep (3);
  smarthome_esp8266_flush (espfd);

  write (espfd, ATE0, sizeof(ATE0));
  usleep (100000);
  return smarthome_esp8266_recv_ok (espfd);
}

// since automatic hotspot connection is set, loop until connected
bool
smarthome_esp8266_connect (int espfd)
{
  do //keep trying to connect to TCP server
    {
      write (espfd, AT_CIPSTART, sizeof(AT_CIPSTART));
      usleep (100000);
    }
  while (!smarthome_esp8266_recv_ok (espfd));
  return true ;
}

bool
smarthome_esp8266_send (int espfd, char* cmd, int len)
{
  char buff[32];
  int numchar;

  numchar = sprintf (buff, "AT+CIPSEND=%d\r\n", len);
  write (espfd, buff, numchar + 1);
  usleep (100000);
  if (!smarthome_esp8266_recv_ok (espfd))
    return false ;

  write (espfd, cmd, len);
  usleep (100000);
  if (!smarthome_esp8266_recv_ok (espfd))
    return false ;

  return true ;
}

void
smarthome_esp8266_send_cmd (int espfd, int selection, bool status[])
{
  char buff[32];
  int bytelen;

  if (selection <= 3)
    { // relay command
      if (status[selection])
	{
	  bytelen = sprintf (buff, "GPIO_RESET%d", selection);
	  smarthome_esp8266_send (espfd, buff, bytelen + 1);
	}
      else
	{
	  bytelen = sprintf (buff, "GPIO_SET%d", selection);
	  smarthome_esp8266_send (espfd, buff, bytelen + 1);
	}
    }
  else
    { // rfid command
      if (status[selection])
	smarthome_esp8266_send (espfd, CARD_REG, sizeof(CARD_REG));
      else
	smarthome_esp8266_send (espfd, CARD_DEL, sizeof(CARD_DEL));
    }
}
