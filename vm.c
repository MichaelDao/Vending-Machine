#include "vm.h"

int main(int argc, char ** argv)
{
    /* Create structures for calling */
    MenuItem menu;
    VmSystem test;

    /* Constant variables for file names */
    const char stockFile = "stock.dat";
    const char coinsFile = "coins.dat";

    /* Print menu */
    initMenu(&menu);

    /* Load the stock file */

    loadStock(&test, stockFile);


    /* Exit the program */
    printf("Goodbye. \n\n");
    return EXIT_SUCCESS;
}
