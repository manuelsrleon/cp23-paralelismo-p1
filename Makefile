CC=gcc
CFLAGS=-g -Wall -O0
LIBS=

PROGS=letras

all: $(PROGS)
	$(CC) $(CFLAGS) -c $<

run: runA runC runG runT

runA:
	./$(PROGS) 100 A

runC:
	./$(PROGS) 100 C

runG:
	./$(PROGS) 100 G

runT:
	./$(PROGS) 100 T

clean:
	rm -f $(PROGS) *.o *~

valgrind-check:
	valgrind --leak-check=full ./$(PROGS)