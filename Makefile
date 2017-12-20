CC=gcc
CFLAGS=-c -g -std=gnu11 -Wall -Wextra
LFLAGS=-lm
OBJ=main.o func.o
TARGET=cm2

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

cleanup:
	rm -f $(OBJ) $(TARGET)
