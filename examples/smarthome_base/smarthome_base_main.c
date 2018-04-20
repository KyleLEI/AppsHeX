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

#include <netutils/esp8266.h>

#include "smarthome_base.h"

sh_state_t g_sh_state = {
	.remote_connected = false,
	.rgb_mode = sh_RGB_BREATH
};

void connectedCB(int socket){
	printf("!!! %d Connected !!!\n",socket);
	g_sh_state.remote_connected=true;
	g_sh_state.rgb_mode = sh_RGB_FLASH_BLUE;
}

void disconnectCB(int socket){
	printf("!!! %d Disconnected !!!\n",socket);
	g_sh_state.remote_connected=false;
	g_sh_state.rgb_mode = sh_RGB_FLASH_RED;
}

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int smarthome_base_main(int argc, char *argv[])
#endif
{
  struct sockaddr_in serv_addr;
  char buff[128]={0};
  ssize_t rsize=0;

  printf("Hello, 3300!!\n");

  printf("Spawning rgbled_daemon\n");
//  task_create("smarthome_rgbled_main", CONFIG_EXAMPLES_SMARTHOME_BASE_PRIORITY,
//		  CONFIG_EXAMPLES_SMARTHOME_BASE_STACKSIZE, smarthome_rgbled_daemon, NULL);
  pthread_create(&g_sh_state.rgbled_thread,NULL,smarthome_rgbled_daemon,(void*)&g_sh_state);
  printf("rgbled_daemon spawned\n");

  printf("Initializing ESP8266\n");
  lesp_initialize();
  lesp_soft_reset();
  printf("ESP8266 has been initialized\n");
  g_sh_state.rgb_mode = sh_RGB_FLASH_GREEN;

  int sockfd=lesp_socket(PF_INET,SOCK_STREAM,0);


  serv_addr.sin_family = PF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(233);

  lesp_bindlistenaccept(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr),
		  connectedCB,disconnectCB);

  do{
	  	if(!g_sh_state.remote_connected||rsize<0) sleep(1);
		rsize = lesp_recv(sockfd, buff, sizeof(buff), 0); //returns -1 if waited too long
		if(rsize>0){
			printf("Received %d bytes: ", rsize);
			fflush(stdout);
			write(1, buff, rsize);
			printf("\n");
		}
  }while(1);

  return 0;
}
