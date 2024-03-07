SRC = src/emi.c src/termios.c
TARGET = bin/emi
CC = gcc
CFLAGS = -Wall -Wextra -pedantic

bin/emi: $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) 

clear: bin/emi
	rm bin/emi
