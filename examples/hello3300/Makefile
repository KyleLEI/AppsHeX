############################################################################
# apps/examples/hello3300/Makefile
#
#   Author: Kyle Lei <leizhao2@gmail.com>
#
############################################################################

-include $(TOPDIR)/Make.defs

# Hello, World! built-in application info

CONFIG_EXAMPLES_HELLO3300_PRIORITY ?= SCHED_PRIORITY_DEFAULT
CONFIG_EXAMPLES_HELLO3300_STACKSIZE ?= 2048

APPNAME = hello3300
PRIORITY = $(CONFIG_EXAMPLES_HELLO3300_PRIORITY)
STACKSIZE = $(CONFIG_EXAMPLES_HELLO3300_STACKSIZE)

# Hello, World! Example

ASRCS =
CSRCS =
MAINSRC = hello3300_main.c

CONFIG_EXAMPLES_HELLO3300_PROGNAME ?= hello3300$(EXEEXT)
PROGNAME = $(CONFIG_EXAMPLES_HELLO3300_PROGNAME)

include $(APPDIR)/Application.mk
