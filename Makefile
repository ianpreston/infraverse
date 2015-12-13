CC=g++
CFLAGS=-std=c++14 -Wall -Werror -pedantic
LDFLAGS=-framework SFML -lsfml-system -lsfml-graphics -lsfml-window -lsfml-network

client: build/client

build/client: src/client/*.cpp
	$(CC) $(CFLAGS) -o build/client $(LDFLAGS) src/client/*.cpp
