CC = gcc
CFLAGS=-Wall -g -Iinclude -o app

# grab all the src
SRC = $(wildcard src/*.c)

# src .c to build/%.o
OBJ = $(SRC:src/%.c=build/%.o)

TARGET = build/app

all: $(TARGET)

# link all files to main exec
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# compile rule for any .c file, $< is the input, $@ is the output
build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ./build