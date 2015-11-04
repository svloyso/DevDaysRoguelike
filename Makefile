CC = g++
CXXFLAGS = -Wall -Werror -std=c++11

EXE = main
BINDIR = bin
SRCDIR = src
OBJECTS = $(BINDIR)/core.o $(BINDIR)/basic.o $(BINDIR)/tile.o $(BINDIR)/main_mock.o

all: $(EXE)

$(EXE): $(BINDIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXE)

bin/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p bin

clean:
	rm -rf $(BINDIR) $(EXE)

.PHONY: clean all

