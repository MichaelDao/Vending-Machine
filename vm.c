#include "vm.h"

int main(int argc, char ** argv)
{
    /* Create structures for calling */
    MenuItem menu;
    VmSystem system;

    /* Constant variables for file names */
    const char stockFileName = "stock.dat";
    const char coinsFileName = "coins.dat";

    /* Print menu */
    initMenu(&menu);

    /* Load the files */
    loadData(&system, stockFileName, coinsFileName);

    displayItems(&system);


    /* Exit the program */
    printf("Goodbye. \n\n");
    return EXIT_SUCCESS;
}
