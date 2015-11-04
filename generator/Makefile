CC = g++
CXXFLAGS = -Wall -Werror -Iinclude -I../core/include -std=c++11 -g

BINDIR = bin
SRCDIR = src
OBJECTS = $(BINDIR)/level.o

all: $(BINDIR) $(OBJECTS) $(TEST)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(BINDIR):
	mkdir -p bin

clean:
	rm -rf $(BINDIR) $(EXE) $(TEST)

.PHONY: clean all