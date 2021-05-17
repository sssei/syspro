CC = gcc
LD = gcc
CFLAGS = -Wall -pthread
LDFLAGS = -pthread
TARGET = tcpechoserver1 tcpechoserver2 tcpechoclient
SRCS := $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.dep)
RM = rm -f

%: %.o
	$(LD) $(LDFLAGS) -o $@ $^

%.dep: %.c
	$(SHELL) -c '$(CC) -MM $< > $@'

-include $(DEPS)

clean:
	$(RM) $(DEPS) $(OBJS) $(TARGET)
