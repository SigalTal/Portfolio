
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(wildcard *.c)
PROJ_SRCS = priority_queue_test.c pq_heap.c

# list of directories containing header files
#PROJ_INC_DIR = $(ROOT_DIR)/include
PROJ_INC_DIR =../../include

# the executable file
PROJ_OUT = pq_heap.out

# list of ADDITIONAL compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =
PROJ_CPPFLAGS =

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS =uid.o heap.o vector.o

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  =../uid/Makefile ../heap/Makefile ../vector/Makefile

include $(ROOT_DIR)/make/Project.mak
