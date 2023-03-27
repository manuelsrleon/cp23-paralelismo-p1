CC=gcc
CFLAGS=-g -Wall -O0
LIBS=

PROGS=letras

all: $(PROGS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(PROGS) *.o *~

valgrind-check:
	valgrind --leak-check=full ./$(PROGS)