CC = g++
CFLAGS = -Wall
LDFLAGS = -lncurses
TARGET = game

all: $(TARGET)

$(TARGET): game.cpp
	$(CC) $(CFLAGS) -o $(TARGET) game.cpp $(LDFLAGS)

clean:
	rm -f $(TARGET)
