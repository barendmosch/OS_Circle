CIRCLEHOME = ../..

OBJS    = main.o kernel.o ledblink.o

LIBS    = $(CIRCLEHOME)/lib/sched/libsched.a \
		$(CIRCLEHOME)/lib/libcircle.a

include $(CIRCLEHOME)/Rules.mk

-include $(DEPS)