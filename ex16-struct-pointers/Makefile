CFLAGS=-Wall -g

default: clean main run

clean:
	rm -f ./main

run:
	./main

lint:
	clang-tidy ./main.c -- std=c11