SOURCES=vm.c vm_menu.c vm_options.c vm_stock.c vm_coin.c utility.c
HEADERS=vm.h vm_menu.h vm_options.h vm_stock.h vm_coin.h utility.h vm_system.h
PROGRAM=vm
DEBUG=-g
FLAGS=-ansi -pedantic -Wall $(DEBUG)

all:
	gcc $(FLAGS) -o $(PROGRAM) $(SOURCES)

clean:
	rm $(PROGRAM)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Makefile
