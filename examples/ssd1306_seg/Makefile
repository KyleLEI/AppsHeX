############################################################################
# apps/examples/ssd1306_seg/Makefile
#
#   Author: Kyle Lei <leizhao2@gmail.com>
#
############################################################################

-include $(TOPDIR)/Make.defs

# SSD1306 alphanumeric driver example built-in application info

CONFIG_EXAMPLES_SSD1306_SEG_PRIORITY ?= SCHED_PRIORITY_DEFAULT
CONFIG_EXAMPLES_SSD1306_SEG_STACKSIZE ?= 2048

APPNAME = ssd1306_seg
PRIORITY = $(CONFIG_EXAMPLES_SSD1306_SEG_PRIORITY)
STACKSIZE = $(CONFIG_EXAMPLES_SSD1306_SEG_STACKSIZE)

# SSD1306 alphanumeric driver Example

ASRCS =
CSRCS =
MAINSRC = ssd1306_seg_main.c

CONFIG_EXAMPLES_SSD1306_SEG_PROGNAME ?= ssd1306_seg$(EXEEXT)
PROGNAME = $(CONFIG_EXAMPLES_SSD1306_SEG_PROGNAME)

include $(APPDIR)/Application.mk
