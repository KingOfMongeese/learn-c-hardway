CFLAGS=-Wall

default: clean program run

clean:
	rm -f program

run:
	./program

lint:
	clang-tidy program.c -- -std=c11


debug: CFLAGS += -g
debug: clean program
