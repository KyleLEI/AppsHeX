/****************************************************************************
 * examples/ssd1306_seg/ssd1306_seg_main.c

 *   Author: Kyle Lei <leizhao2@gmail.com>

 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <nuttx/lcd/ssd1306_seg.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef EXAMPLES_SSD1306_SEG_DEVNAME
#  define EXAMPLES_SSD1306_SEG_DEVNAME "/dev/slcd0"
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * hello_main
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int ssd1306_seg_main(int argc, char *argv[])
#endif
{
	int fd;
	int ret;
	char buffer[32];

	/* Open the SSD1306 alphanumeric driver */
	fd = open(EXAMPLES_SSD1306_SEG_DEVNAME, O_RDWR | O_NONBLOCK);
	if (fd < 0) {
		int errcode = errno;
		printf("ERROR: Failed to open %s: %d\n",
		EXAMPLES_SSD1306_SEG_DEVNAME, errcode);
		goto errout;
	}

	/* Clear the screen */
	ret = ioctl(fd, SLCDIOC_CLEAR, 0);

	if (ret < 0) {
		int errcode = errno;
		printf("ssd1306_seg: ERROR: ioctl(SLCDIOC_CLEAR) failed: %d\n",
				errcode);
		goto errout;
	}

	sprintf(buffer,"\x01\x01Hello from main!");

	ret = write(fd,buffer,sizeof(buffer));

	if (ret < 0) {
		int errcode = errno;
		printf("ssd1306_seg: ERROR: write failed: %d\n",
				errcode);
		goto errout;
	}


	return 0;
errout:
	return EXIT_FAILURE;

}
