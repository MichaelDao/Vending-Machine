#/******************************************************************************

#** Student Name: <Michael Dao>

#** Student Number: <s3668300>

#** Date of submission: <13/10/2017>

#** Course: COSC1076 / COSC2207, Semester 2, 2017

#******************************************************************************/

CFLAGS=-ansi -Wall -pedantic
LFLAGS=
EXECUTABLE= vm
GAME_OBJECTS=vm.o vm_menu.o vm_options.o vm_stock.o vm_coin.o utility.o
		SOURCES=vm.c vm_menu.c vm_options.c vm_stock.c vm_coin.c utility.c
		HEADERS=vm.h vm_menu.h vm_options.h vm_stock.h vm_coin.h utility.h vm_system.h

all: ${EXECUTABLE}

%.o:%.c ${HEADERS}
gcc ${CFLAGS} -c $<

		vm:${GAME_OBJECTS}
gcc ${LFLAGS} $^ -o $@

.PHONY:clean
clean:
		rm ${GAME_OBJECTS} ${EXECUTABLE}

archive:
		zip s3668300-a2 $(SOURCES) $(HEADERS) Makefile valgrind_Log