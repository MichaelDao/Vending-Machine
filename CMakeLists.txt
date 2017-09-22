cmake_minimum_required(VERSION 3.8)
project(Vending_Machine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        coins.dat
        Makefile
        cmake-build-debug/stock.dat
        utility.c
        utility.h
        vm
        vm.c
        vm.h
        vm_coin.c
        vm_coin.h
        vm_menu.c
        vm_menu.h
        vm_options.c
        vm_options.h
        vm_stock.c
        vm_stock.h
        vm_system.h)

add_executable(Vending_Machine ${SOURCE_FILES})