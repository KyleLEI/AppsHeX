############################################################################
# apps/examples/ledc/Makefile
#
#   Author: Kyle Lei
#
############################################################################

-include $(TOPDIR)/Make.defs

# LED driver test built-in application info

CONFIG_EXAMPLES_LEDC_PRIORITY ?= SCHED_PRIORITY_DEFAULT
CONFIG_EXAMPLES_LEDC_STACKSIZE ?= 2048

APPNAME = ledc
PRIORITY = $(CONFIG_EXAMPLES_LEDC_PRIORITY)
STACKSIZE = $(CONFIG_EXAMPLES_LEDC_STACKSIZE)

# LED driver test

ASRCS =
CSRCS =
MAINSRC = ledc_main.c

CONFIG_EXAMPLES_LEDC_PROGNAME ?= ledc$(EXEEXT)
PROGNAME = $(CONFIG_EXAMPLES_LEDC_PROGNAME)

include $(APPDIR)/Application.mk
