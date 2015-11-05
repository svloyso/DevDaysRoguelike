CC = g++
CXXFLAGS = -Wall -Werror -Iinclude -std=c++11 -g

TEST = test
BINDIR = bin
SRCDIR = src
TESTDIR = tests
TEST_OBJ = $(BINDIR)/test_tiles.o

include MakeList

all: $(BINDIR) $(COREOBJ)

$(TEST): $(BINDIR) $(COREOBJ) $(TEST_OBJ)
	$(CC) $(COREOBJ) $(TEST_OBJ) -o $(TEST)

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

