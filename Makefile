CC = clang++

FLAGS = -Wall
DBGFLAGS = -Wall -ggdb3

BUILDDIR = build

SRCFILES = $(wildcard src/*.cpp)
SRCNODIR = $(SRCFILES:src/%=%)
OBJREL = $(addprefix $(BUILDDIR)/linux/release/obj/, $(SRCNODIR:.cpp=.o))
OBJDBG = $(addprefix $(BUILDDIR)/linux/debug/obj/, $(SRCNODIR:.cpp=.o))

all: builddirs release debug

builddirs:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/linux
	mkdir -p $(BUILDDIR)/linux/release $(BUILDDIR)/linux/debug
	mkdir -p $(BUILDDIR)/linux/release/obj $(BUILDDIR)/linux/debug/obj

release: $(OBJREL)
	$(CC) $(OBJREL) -o $(BUILDDIR)/linux/release/k5

$(BUILDDIR)/linux/release/obj/%.o: src/%.cpp
	$(CC) -c $(FLAGS) $< -o $@

debug: $(OBJDBG)
	$(CC) $(OBJDBG) -o $(BUILDDIR)/linux/debug/k5

$(BUILDDIR)/linux/debug/obj/%.o: src/%.cpp
	$(CC) -c $(DBGFLAGS) $< -o $@

clean:
	rm -rf build