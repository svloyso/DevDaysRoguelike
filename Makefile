CC = g++

EXE = main
BINDIR = bin
SRCDIR = src
COREDIR = core
GENERATORDIR = generator
UIDIR = UI

CXXFLAGS = -Wall -Werror -std=c++11 -I$(COREDIR)/include -I$(GENERATORDIR)/include -I$(UIDIR)/include

include $(COREDIR)/MakeList
include $(GENERATORDIR)/MakeList
include $(UIDIR)/MakeList

OTHEROBJ = bin/test.o

all: $(EXE)

$(EXE): $(BINDIR) $(OTHEROBJ) $(COREOBJ) $(GENERATOROBJ) # $(UIOBJ)
	$(CC) -o $(EXE) $(OTHEROBJ) $(COREOBJ) $(GENERATOROBJ) # $(UIOBJ) 

$(BINDIR)/%.o: $(COREDIR)/$(SRCDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -MMD -o $@ $<

$(BINDIR)/%.o: $(GENERATORDIR)/$(SRCDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -MMD -o $@ $<

$(BINDIR)/%.o: $(UIDIR)/$(SRCDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -MMD -o $@ $<

$(BINDIR)/%.o: %.cpp
	$(CC) $(CXXFLAGS) -c -MMD -o $@ $<


include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p bin

clean:
	rm -rf $(BINDIR) $(EXE)

.PHONY: clean all

