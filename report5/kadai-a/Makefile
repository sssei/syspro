CC = gcc
LD = gcc
CFLAGS = -Wall 
LDFLAGS = 
TARGET = myexec
SRCS := $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.dep)
RM = rm -f

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# $(OBJS): $(SRCS)
# 	$(CC) -c $(CFLAGS) -o $@ $^

%.dep: %.c
	$(SHELL) -c '$(CC) -MM $< > $@'

-include $(DEPS)

clean:
	$(RM) $(TARGET) $(DEPS) $(OBJS)
