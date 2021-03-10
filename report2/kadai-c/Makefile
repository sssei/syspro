CC = gcc
LD = gcc
CFLAGS = -Wall
LDFLAGS =
TARGET = all
SRCS := $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.dep)
RM = rm -f

all: measure1 measure2 measure3

measure1: measure1.o mycp.o
	$(LD) $(LDFLAGS) -o $@ $^

measure2: measure2.o mycp2.o 
	$(LD) $(LDFLAGS) -o $@ $^

measure3: measure3.o mycp3.o
	$(LD) $(LDFLAGS) -o $@ $^

%.dep: %.c
	$(SHELL) -c '$(CC) -MM $< > $@'

-include $(DEPS)

clean:
	$(RM) $(TARGET) $(DEPS) $(OBJS) measure1 measure2 measure3

.PHONY: all clean


