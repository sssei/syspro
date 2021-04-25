CC = gcc
LD = gcc
CFLAGS = -Wall -pthread -g 
LDFLAGS = -pthread
TARGET = test
SRCS := $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.dep)
RM = rm -f

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.dep: %.c
	$(SHELL) -c '$(CC) -MM $< > $@'

-include $(DEPS)

clean:
	$(RM) $(TARGET) $(DEPS) $(OBJS)
