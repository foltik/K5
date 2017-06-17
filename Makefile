CC = clang++
AR = ar

LIBFLAGS = -lGl
FLAGS = -Wall -std=c++11 -I/usr/include/freetype2
DBGFLAGS = -Wall -ggdb3 -std=c++11 -I/usr/include/freetype2

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
	$(AR) rcs $(BUILDDIR)/linux/release/k5.a $(OBJREL)

$(BUILDDIR)/linux/release/obj/%.o: src/%.cpp
	$(CC) -c $(FLAGS) $< -o $@

debug: $(OBJDBG)
	$(AR) rcs $(BUILDDIR)/linux/debug/k5.a $(OBJDBG)

$(BUILDDIR)/linux/debug/obj/%.o: src/%.cpp
	$(CC) -c $(DBGFLAGS) $< -o $@

resource:
	cp -r res $(BUILDDIR)/linux/release
	cp -r res $(BUILDDIR)/linux/debug

install:
	sudo mkdir -p /usr/local/include/k5
	sudo cp -r src/*.h /usr/local/include/k5/
	sudo cp build/linux/release/k5.a /usr/local/lib/

clean:
	rm -rf build
