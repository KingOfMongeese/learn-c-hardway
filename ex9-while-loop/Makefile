CFLAGS=-Wall

default: clean main run

clean:
	rm -f main

run:
	./main

debug: CLFAGS += -g
debug: clean main

lint:
	clang-tidy main.c -- std=c11