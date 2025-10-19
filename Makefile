CC = gcc
CFLAGS = -O2 -Wall -Iinclude
SRC = src/main.c src/file_read.c src/file_mmap.c src/crc64.c src/timer.c
OUT = lab1

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
