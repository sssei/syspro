CC = gcc
CFLAGS = -Wall
DEPS = b.h c.h
OBJ = a.o b.o c.o

kadai-a: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) kadai-a
