CPPFLAGS = -Wall  -std=c++11 
CC = g++

all: bin/main
	mkdir -p bin

bin/main: bin/main.o bin/console_graphic.o bin/consoleprint.o bin/drawinfo.o bin/gameprocess.o
	mkdir -p bin
	$(CC) $(CPPFLAGS) bin/main.o bin/console_graphic.o -o bin/main -lncurses

bin/main.o: src/main.cpp 
	mkdir -p bin
	$(CC) $(CPPFLAGS) -c src/main.cpp -o bin/main.o -lncurses

bin/consoleprint.o: src/consoleprint.cpp 
	mkdir -p bin
	$(CC) $(CPPFLAGS) -c src/consoleprint.cpp -o bin/consoleprint.o -lncurses

bin/console_graphic.o: src/console_graphic.cpp
	mkdir -p bin
	$(CC) $(CPPFLAGS) -c src/console_graphic.cpp -o bin/console_graphic.o -lncurses

bin/drawinfo.o: src/drawinfo.cpp
	mkdir -p bin
	$(CC) $(CPPFLAGS) -c src/drawinfo.cpp -o bin/drawinfo.o -lncurses

bin/gameprocess.o: src/gameprocess.cpp
	mkdir -p bin
	$(CC) $(CPPFLAGS) -c src/gameprocess.cpp -o bin/gameprocess.o -lncurses

clean:
	rm -rf bin

.PHONY: clean all



