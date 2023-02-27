.PHONY: all run clean

CC = gcc
CFLAGS = -g -Wall

SRC = main.c bmp.c
OBJ = $(patsubst %.c, %.o, $(SRC))
TARGET = main.out

all: $(TARGET)

run:
	./$(TARGET)

clean:
	rm *.o *.out *.output.bmp

$(TARGET): $(OBJ) 
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<