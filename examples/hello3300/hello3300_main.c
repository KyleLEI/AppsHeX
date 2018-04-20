/****************************************************************************
 * examples/hello3300/hello3300_main.c

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

#include <netutils/esp8266.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/
extern int rgbled_main(int argc, char *argv[]);
/****************************************************************************
 * hello_main
 ****************************************************************************/
bool connected=false;

void connectedCB(int socket){
	printf("!!! %d Connected !!!\n",socket);
	connected=true;
}

void disconnectCB(int socket){
	printf("!!! %d Disconnected !!!\n",socket);
	connected=false;
}

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int hello3300_main(int argc, char *argv[])
#endif
{
  struct sockaddr_in serv_addr;
  char buff[128]={0};
  ssize_t rsize=0;

  printf("Hello, 3300!!\n");

  printf("Spawning rgbled_main\n");
  task_create("rgbled_main", CONFIG_EXAMPLES_HELLO3300_PRIORITY,
  	CONFIG_EXAMPLES_HELLO3300_STACKSIZE, rgbled_main, NULL);
  printf("rgbled_main spawned\n");

  printf("Initializing ESP8266\n");
  lesp_initialize();
  lesp_soft_reset();
  printf("ESP8266 has been initialized\n");

  int sockfd=lesp_socket(PF_INET,SOCK_STREAM,0);


  serv_addr.sin_family = PF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(233);

  lesp_bindlistenaccept(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr),
		  connectedCB,disconnectCB);

  do{
	  	if(!connected||rsize<0) sleep(1);
		rsize = lesp_recv(sockfd, buff, sizeof(buff), 0);
		printf("Received %d bytes: ", rsize);
		fflush(stdout);
		write(1, buff, rsize);
		printf("\n");
  }while(1);

  return 0;
}
