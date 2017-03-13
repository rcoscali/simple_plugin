##
## Use GCC as the target gcc
## Use CXX as the target g++
## Use CC as the host gcc
## Use CXX as the host g++
##
## For example:
## use
# make GCC=arc-elf32-gcc GXX=arc-elf32-g++ CC=gcc CXX=g++ all check test
## for building plugin for arc gcc
## use
# make all check test
## for building plugin for host gcc

GCC := gcc
GXX := g++

GXXFLAGS := -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm

CC := $(GCC)
CXX := $(GXX)

CXXFLAGS := -std=c++11 -Wall -fno-rtti -Wno-literal-suffix -fPIC
GCC_PLUGIN_DIR=$(shell $(GCC) -print-file-name=plugin)

CPPFLAGS += -I$(GCC_PLUGIN_DIR)/include

all: simple.so

simple.so: simple.o
	$(CXX) $(LDFLAGS) -shared -o $@ $<

%.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f *.o *.so *~ *.s *.S *.i *.ii
	rm -f *.dot *.dot.*
	rm -f *.c.*.* *.cc.*.*
	rm -f \#*\#

install:
	sudo cp -vf simple.so $(GCC_PLUGIN_DIR)

check: simple.so install
	$(GXX) $(GXXFLAGS) -fplugin=$(GCC_PLUGIN_DIR)/simple.so -c -x c++ /dev/null -o /dev/null

test: simple.so install
	$(GXX) $(GXXFLAGS) -da -dv -fplugin=$(GCC_PLUGIN_DIR)/simple.so -c -x c++ test.cc -o test.o

chkadd.s: chkadd.c
	$(GXX) $(GXXFLAGS) -da -dv -fplugin=$(GCC_PLUGIN_DIR)/simple.so -S -x c chkadd.c -o chkadd.s

chkadd: simple.so install chkadd.s
	$(GXX) $(GXXFLAGS) -da -dv -fplugin=$(GCC_PLUGIN_DIR)/simple.so -c -x c++ chkadd.c -o chkadd.o

.PHONY: all clean install check test chkadd

