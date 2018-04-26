############################################################################
# apps/examples/smarthome_remote/Makefile
#
#   Author: Kyle Lei <leizhao2@gmail.com>
#
############################################################################

-include $(TOPDIR)/Make.defs

# Hello, World! built-in application info

CONFIG_EXAMPLES_SMARTHOME_REMOTE_PRIORITY ?= SCHED_PRIORITY_DEFAULT
CONFIG_EXAMPLES_SMARTHOME_REMOTE_STACKSIZE ?= 1024

APPNAME = smarthome_remote
PRIORITY = $(CONFIG_EXAMPLES_SMARTHOME_REMOTE_PRIORITY)
STACKSIZE = $(CONFIG_EXAMPLES_SMARTHOME_REMOTE_STACKSIZE)

# Hello, World! Example

ASRCS =
CSRCS = smarthome_oled.c smarthome_esp8266.c
MAINSRC = smarthome_remote_main.c

CONFIG_EXAMPLES_SMARTHOME_REMOTE_PROGNAME ?= smarthome_remote$(EXEEXT)
PROGNAME = $(CONFIG_EXAMPLES_SMARTHOME_REMOTE_PROGNAME)

include $(APPDIR)/Application.mk
