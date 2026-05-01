CFLAGS=-Wall

default: clean main run

clean:
	rm -f ./main

run:
	./main test ooo wow

lint:
	clang-tidy ./main.c -- std=c11