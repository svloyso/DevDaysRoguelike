CC = g++
CXXFLAG = -Wall -Werror

OBJECTS = #put your object files here
EXE = main
BINDIR = bin
SRCDIR = src

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

