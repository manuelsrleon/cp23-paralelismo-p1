CC=mpicc
CFLAGS=-g -Wall -O0
LIBS=

PROGS=letras

all: $(PROGS)
	$(CC) $(CFLAGS) -c $< -lm
run: run100

run100: run100A run100C run100G run100T

run100A:
	mpirun ./$(PROGS) 100 A

run100C:
	mpirun ./$(PROGS) 100 C

run100G:
	mpirun ./$(PROGS) 100 G

run100T:
	mpirun ./$(PROGS) 100 T

runv: run100v

run100v: run100Av run100Cv run100Gv run100Tv

run100Av:
	mpirun ./$(PROGS) 100 A v

run100Cv:
	mpirun ./$(PROGS) 100 C v

run100Gv:
	mpirun ./$(PROGS) 100 G v

run100Tv:
	mpirun ./$(PROGS) 100 T v
clean:
	rm -f $(PROGS) *.o *~

valgrind-check:
	valgrind --leak-check=full ./$(PROGS)