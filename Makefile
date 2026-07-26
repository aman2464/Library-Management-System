CC = gcc
CFLAGS = -Iinclude -Wall
SRC = main.c src/library.c
TARGET = library_app

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)