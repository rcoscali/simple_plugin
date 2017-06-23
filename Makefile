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

ifeq ($(USE_GCC),5)
GCC := /usr/local/gcc-5.4.0-linux-x86_64/bin/gcc
GXX := /usr/local/gcc-5.4.0-linux-x86_64/bin/g++
GDB := /usr/local/gcc-5.4.0-linux-x86_64/bin/gdb
else
GCC := /usr/local/gcc-6.3.0-linux-x86_64/bin/gcc
GXX := /usr/local/gcc-6.3.0-linux-x86_64/bin/g++
GDB := /usr/local/gcc-6.3.0-linux-x86_64/bin/gdb
endif

GXXFLAGS := -g -O0 -da -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm
GXXPLUGINFLAGS := -fplugin=$(shell $(GCC) -print-file-name=plugin)/simple.so
GDBFLAGS := -q -args $(shell $(GCC) -print-file-name=cc1) -O3

LDFLAGS := -g -O0

CC := $(GCC)
CXX := $(GXX)

CXXFLAGS := -g -O0 -std=c++11 -Wall -fno-rtti -Wno-literal-suffix -fPIC
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
	$(GXX) $(GXXFLAGS) $(GXXPLUGINFLAGS) -c -x c++ /dev/null -o /dev/null

test: simple.so install
	$(GXX) $(GXXFLAGS) -S -x c++ test.cc -o test.s >/dev/null 2>/dev/null
	/bin/echo -ne "digraph {\n" > graph_test.dot
	$(GXX) $(GXXFLAGS) $(GXXPLUGINFLAGS) -fdump-tree-all -fplugin-arg-simple-graphname=graph_test -c -x c++ test.cc -o test.o >simple.log 2>&1 
	/bin/echo -ne "\n}\n" >> graph_test.dot
	dot -Tsvg -O graph_test.dot
	echo ";;# ndisasm -b 64 -p intel -e $$((0x`readelf -S test.o | grep -w -A1 \.text | head -1 | awk '{print \$$6}'`)) -k $$((0x`readelf -S test.o | grep -w -A1 \.text | tail -1 | awk '{print \$$1}'`)),`/bin/ls -l test.o | awk '{print $$5}'` test.o" > test.S
	ndisasm -b 64 -p intel -e $$((0x`readelf -S test.o | grep -w -A1 \.text | head -1 | awk '{print \$$6}'`)) -k $$((0x`readelf -S test.o | grep -w -A1 \.text | tail -1 | awk '{print \$$1}'`)),`/bin/ls -l test.o | awk '{print $$5}'` test.o >> test.S

debugtest: simple.so install
	/bin/echo -ne "digraph {\n" > graph_test.dot
	gdb -q -args /usr/local/gcc-6.3.0-linux-x86_64/libexec/gcc/x86_64-linux-gnu/6.3.0/cc1plus -O1 $(GXXPLUGINFLAGS) -fplugin-arg-simple-graphname=graph_test
	/bin/echo -ne "\n}\n" >> graph_test.dot
	dot -Tsvg -O graph_test.dot

chkadd.s: chkadd.c
	$(GXX) $(GXXFLAGS) -S -x c chkadd.c -o chkadd.s

chkadd: simple.so install chkadd.s
	/bin/echo -ne "digraph {\n" > graph_chkadd.dot
	$(GXX) $(GXXFLAGS) $(GXXPLUGINFLAGS) -fplugin-arg-simple-graphname=graph_chkadd -c -x c++ chkadd.c -o chkadd.o
	/bin/echo -ne "\n}\n" >> graph_chkadd.dot
	dot -Tsvg -O graph_chkadd.dot

.PHONY: all clean install check test debugtest chkadd
