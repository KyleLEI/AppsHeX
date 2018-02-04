/****************************************************************************
 * examples/leds/leds_main.c
 *
 *   Copyright (C) 2016 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/ioctl.h>
//#include <stdbool.h>
//#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

#include <nuttx/leds/userled.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * leds_main
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int ledc_main(int argc, FAR char *argv[])
#endif
{
	if(argc<2){
		printf("Usage: ledc on/off\n");
		return 1;
	}
	userled_set_t supported;
	userled_set_t ledset;
//	printf("ledc: Opening %s\n", CONFIG_EXAMPLES_LEDC_DEVPATH);
	int fd=open(CONFIG_EXAMPLES_LEDC_DEVPATH, O_WRONLY);
	if (fd < 0){
	      int errcode = errno;
	      printf("led_daemon: ERROR: open failed: %d\n",
	             errcode);
	      return 1;
	}
	int ret=ioctl(fd, ULEDIOC_SUPPORTED,
            (unsigned long)((uintptr_t)&supported));
	if (ret < 0){
		int errcode = errno;
    	printf("ledc: ERROR: ioctl(ULEDIOC_SUPPORTED) failed: %d\n",
           errcode);
    	return 1;
	}
	//printf("ledc: Supported LEDs 0x%02x\n", (unsigned int)supported);

	if (!strcmp(argv[1],"on")){
		printf("Turning on LED\n");
		ledset=supported&0x00;
	}else {
		printf("Turning off LED\n");
		ledset=supported&0xFF;
	}

	ret = ioctl(fd, ULEDIOC_SETALL, ledset);//setting
	if (ret < 0) {
		int errcode = errno;
		printf("ledc: ERROR: ioctl(ULEDIOC_SUPPORTED) failed: %d\n",
				errcode);
		return 1;
	}
	return ret;
}
