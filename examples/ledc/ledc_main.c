/****************************************************************************
 * examples/ledc/ledc_main.c
 *
 *   Author: Kyle Lei <leizhao2@gmail.com>
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
#include <stdlib.h>
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
		printf("Usage: ledc [LED_ID] on/off\n");
		return 1;
	}

	userled_set_t ledset;
	userled_set_t supported;
	printf("ledc: Opening %s\n", CONFIG_EXAMPLES_LEDC_DEVPATH);
	int fd=open(CONFIG_EXAMPLES_LEDC_DEVPATH, O_WRONLY);
	if (fd < 0){
	      int errcode = errno;
	      printf("ledc: ERROR: open failed: %s\n",
	             strerror(errcode));
	      return 1;
	}

	int ret;
	ret = ioctl(fd, ULEDIOC_SUPPORTED,
			(unsigned long) ((uintptr_t) &supported));
	if (ret < 0) {
		int errcode = errno;
		printf("ledc: ERROR: ioctl(ULEDIOC_SUPPORTED) failed: %s\n",
				strerror(errcode));
		return 1;
	}
	printf("ledc: Supported LEDs 0x%02x\n", (unsigned int) supported);

	if (argc == 2) {
		if (!strcmp(argv[1], "on")) {
			printf("Turning on LED\n");
			ledset = supported & 0x00;
		} else {
			printf("Turning off LED\n");
			ledset = supported & 0xFF;
		}
	} else {
		userled_set_t ledstatus;
		ret = ioctl(fd, ULEDIOC_GETALL,
				(unsigned long) ((uintptr_t) &ledstatus));
		if (ret < 0) {
			int errcode = errno;
			printf("ledc: ERROR: ioctl(ULEDIOC_GETALL) failed: %s\n",
					strerror(errcode));
			return 1;
		}
		printf("ledc: LEDs status 0x%02x\n", (unsigned int)ledstatus);
		int setled = atoi(argv[1]);
		if (!strcmp(argv[2], "on")) {
			printf("Turning on LED%d\n", setled);
			ledset = ledstatus & ~setled;
		} else {
			printf("Turning off LED%d\n", setled);
			ledset = ledstatus | setled;
		}
	}

	ret = ioctl(fd, ULEDIOC_SETALL, ledset);//setting
	if (ret < 0) {
		int errcode = errno;
		printf("ledc: ERROR: ioctl(ULEDIOC_SUPPORTED) failed: %s\n",
				strerror(errcode));
		return 1;
	}
	return ret;
}
