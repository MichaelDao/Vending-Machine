#include "vm.h"

int main(int argc, char ** argv)
{
    /* Create structures for calling */
    MenuItem menu;
    VmSystem system;

    /* Initialize the system TODO Ensure boolean is used*/
    systemInit(&system);

    /* Constant variables for file names TODO make it 'argc' and 'argv' instead of manual names*/
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
