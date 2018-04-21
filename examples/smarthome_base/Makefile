############################################################################
# apps/examples/hello3300/Makefile
#
#   Author: Kyle Lei <leizhao2@gmail.com>
#
############################################################################

-include $(TOPDIR)/Make.defs

# Hello, World! built-in application info

CONFIG_EXAMPLES_SMARTHOME_BASE_PRIORITY ?= SCHED_PRIORITY_DEFAULT
CONFIG_EXAMPLES_SMARTHOME_BASE_STACKSIZE ?= 2048

APPNAME = smarthome_base
PRIORITY = $(CONFIG_EXAMPLES_SMARTHOME_BASE_PRIORITY)
STACKSIZE = $(CONFIG_EXAMPLES_SMARTHOME_BASE_STACKSIZE)

# Hello, World! Example

ASRCS =
CSRCS = smarthome_rgbled_daemon.c smarthome_gpio.c
MAINSRC = smarthome_base_main.c

CONFIG_EXAMPLES_SMARTHOME_BASE_PROGNAME ?= smarthome_base$(EXEEXT)
PROGNAME = $(CONFIG_EXAMPLES_SMARTHOME_BASE_PROGNAME)

include $(APPDIR)/Application.mk
