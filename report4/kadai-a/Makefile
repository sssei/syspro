CC = gcc
LD = gcc
CFLAGS = -Wall 
LDFLAGS = 
SERVER = udpechoserver
CLIENT = udpechoclient
SRCS := $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.dep)
RM = rm -f

$(SERVER): $(SERVER).o
	$(LD) $(LDFLAGS) -o $@ $^

$(CLIENT): $(CLIENT).o
	$(LD) $(LDFLAGS) -o $@ $^

%.dep: %.c
	$(SHELL) -c '$(CC) -MM $< > $@'

-include $(DEPS)

clean:
	$(RM) $(SERVER) $(CLIENT) $(DEPS) $(OBJS)
