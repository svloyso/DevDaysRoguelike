CC = g++
CXXFLAGS = -Wall -Werror -Iinclude -std=c++11 -g

TEST = test
BINDIR = bin
SRCDIR = src
TESTDIR = tests
OBJECTS = $(BINDIR)/core.o $(BINDIR)/basic.o $(BINDIR)/tile.o $(BINDIR)/visitor.o
TEST_OBJ = $(BINDIR)/test_tiles.o

all: $(BINDIR) $(OBJECTS)

$(TEST): $(BINDIR) $(OBJECTS) $(TEST_OBJ)
	$(CC) $(OBJECTS) $(TEST_OBJ) -o $(TEST)

$(BINDIR)/%.o: $(TESTDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -MMD -o $@ $<

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p bin

clean:
	rm -rf $(BINDIR) $(EXE) $(TEST)

.PHONY: clean all

