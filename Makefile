CC = gcc
CFLAGS = -Wall -O2
LIBS = -lm -lreadline

all: calculate

calculate:calculate.c stack.c stack.h
	$(CC) $(CFLAGS) -o calculate calculate.c stack.c $(LIBS)

run: calculate
	./calculate

clean:
	rm -f calculate
