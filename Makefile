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
##
## use
# make all check test
## for building plugin for host gcc
##
## use
# make USE_GCC=6 all check test
## for building plugin for host gcc rebuilt and installed in /usr/local/gcc-6.3.0-linux-x86_64
##
## use
# make USE_GCC=5 all check test
## for building plugin for host gcc rebuilt and installed in /usr/local/gcc-5.4.0-linux-x86_64
##
## use
# make USE_GCC=gcc-6 all check test
## for building plugin for host gcc gcc-6

ADD_CODE_ON_EDGE = 0
ADD_CODE_ON_BB = 1
ADD_GIMPLE_NOP_ON_BB = 1
ADD_GIMPLE_ASM_ON_BB = 0

ifeq ($(USE_GCC),5)
## Use a rebuilt gcc 5.4.0 installed in /usr/local/gcc-5.4.0-linux-x86_64
GCC := /usr/local/gcc-5.4.0-linux-x86_64/bin/gcc
GXX := /usr/local/gcc-5.4.0-linux-x86_64/bin/g++
GXX_CC1PLUS := $(dir $(GXX))/../libexec/gcc/x86_64-linux-gnu/5.4.0/cc1plus
GDB := gdb
USE_GCC_6_FLAGS := -UUSE_GCC_6
ADD_CODE_ON_EDGE ?= 0
else
## Use a rebuilt gcc 6.3.0 installed in /usr/local/gcc-6.3.0-linux-x86_64
ifeq ($(USE_GCC),6)
GCC := /usr/local/gcc-6.3.0-linux-x86_64/bin/gcc
GXX := /usr/local/gcc-6.3.0-linux-x86_64/bin/g++
GXX_CC1PLUS := $(dir $(GXX))/../libexec/gcc/x86_64-linux-gnu/6.3.0/cc1plus
GDB := gdb
USE_GCC_6_FLAGS := -DUSE_GCC_6
ADD_CODE_ON_EDGE ?= 1
else
ifeq ($(USE_GCC),gcc-6)
GCC := gcc-6
GXX := g++-6
GDB := gdb
USE_GCC_6_FLAGS := -DUSE_GCC_6
ADD_CODE_ON_EDGE ?= 1
else
GCC := gcc
GXX := g++
GDB := gdb
USE_GCC_6_FLAGS := -UUSE_GCC_6
ADD_CODE_ON_EDGE ?= 0
endif
endif
endif

GXX_CPPFLAGS := $(USE_GCC_6_FLAGS)
ifeq ($(ADD_GIMPLE_NOP_ON_EDGE),1)
GXX_CPPFLAGS += -DADD_GIMPLE_NOP_ON_EDGE
endif
ifeq ($(ADD_GIMPLE_NOP_ON_BB),1)
GXX_CPPFLAGS += -DADD_GIMPLE_NOP_ON_BB
endif
ifeq ($(ADD_GIMPLE_ASM_ON_EDGE),1)
GXX_CPPFLAGS += -DADD_GIMPLE_ASM_ON_EDGE
endif
ifeq ($(ADD_GIMPLE_ASM_ON_BB),1)
GXX_CPPFLAGS += -DADD_GIMPLE_ASM_ON_BB
endif
GXX_CPPFLAGS += \
	-DADD_CODE_ON_EDGE=$(ADD_CODE_ON_EDGE) \
	-DADD_CODE_ON_BB=$(ADD_CODE_ON_BB)

GXXFLAGS := -g -O0 -std=c++11 -fPIC -fno-rtti $(GXX_CPPFLAGS)
GXXPLUGINFLAGS := -fplugin=$(shell $(GCC) -print-file-name=plugin)/simple.so
GDBFLAGS := -q -args $(shell $(GCC) -print-file-name=cc1) -O3

LDFLAGS := -g -O0

CC := $(GCC)
CXX := $(GXX)

CXXFLAGS := -g -O0 -std=c++11 -da -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm -Wall -fno-rtti -Wno-literal-suffix -fPIC
GCC_PLUGIN_DIR=$(shell $(GCC) -print-file-name=plugin)

CPPFLAGS += -I$(GCC_PLUGIN_DIR)/include

%.o: %.cc
	$(CXX) $(GXXFLAGS) $(CPPFLAGS) -c -o $@ $^

all: dump_vars simple.so

dump_vars:
	@echo "GCC := $(GCC)"
	@echo "GXX := $(GXX)"
	@echo "GDB := $(GDB)"

simple.so: simple.o
	$(CXX) $(LDFLAGS) -shared -o $@ $< 

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
	$(GXX) $(CXXFLAGS) -S -x c++ test.cc -o test.s
	/bin/echo -ne "digraph {\n" > graph_test.dot
	$(GXX) $(CXXFLAGS) $(GXXPLUGINFLAGS) -fdump-tree-all-graph -fdump-tree-all -fplugin-arg-simple-graphname=graph_test -c -x c++ test.cc -o test.o >simple.log 2>&1 
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
