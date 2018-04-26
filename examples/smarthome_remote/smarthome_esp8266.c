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
#include <poll.h>

#include "smarthome_remote.h"

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
  char c;
  int ret;
//  struct pollfd fds[1];
//  char buff[16];
//
//  memset (fds, 0, sizeof(struct pollfd));
//  fds[0].fd = espfd;
//  fds[0].events = POLLIN;
//
//  ret = poll(fds, 1, 1000);
//
//  if (ret < 0)
//    {
//      return false;
//    }
//  else if ((fds[0].revents & POLLERR) && (fds[0].revents & POLLHUP))
//    {
//      return false;
//    }
//  else if (fds[0].revents & POLLIN)
//    {
//      ret = read(espfd, buff, sizeof(buff));
//      printf("Received %d bytes\n",ret);
//      write(1,buff,ret);
//    }
//
//  if (ret < 0)
//    {
//      return false;
//    }
  ret = read (espfd, &c, 1); // probably need debugging here

  printf("%d bytes read\n",ret);

  if(c=='\r'){
      read (espfd, &c, 1);
      read (espfd, &c, 1);
      read (espfd, &c, 1);
      read (espfd, &c, 1);
      read (espfd, &c, 1);
      read (espfd, &c, 1);
  }

  return false ;
}
/****************************************************************************
 * Public Functions
 ****************************************************************************/
bool
smarthome_esp8266_init (int espfd)
{
  int ret;
  sleep (1);
//  ret = smarthome_esp8266_send_cmd (espfd, "AT+RST\r\n");
//  smarthome_esp8266_recv_ok (espfd);
//  printf ("%d bytes written\n", ret);
//  smarthome_esp8266_flush (espfd);
  ret = smarthome_esp8266_send_cmd (espfd, "ATE0\r\n");
  printf ("%d bytes written\n", ret);
  sleep(1);
  return smarthome_esp8266_recv_ok (espfd);
}
