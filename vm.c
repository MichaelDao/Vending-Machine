/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <NULL>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm.h"

int main(int argc, char ** argv)
{
    /* Create structures for calling */
    MenuItem menu;
    VmSystem system;
    MenuFunction option;

    /* Initialize menu */
    initMenu(&menu);

    /* Initialize the system TODO Ensure boolean is used*/
    systemInit(&system);



    /* Constant variables for file names TODO make it 'argc' and 'argv' instead of manual names*/
    const char stockFileName = "stock.dat";
    const char coinsFileName = "coins.dat";

    /* Load the files */
    loadData(&system, stockFileName, coinsFileName);

    for(;;)
    {
        /* Print menu and ask for choice */
        option = getMenuChoice(&menu);

        if (option == saveAndExit)
            break;
        else if (option == NULL)
            continue;
        else
            (*option)(&system);
    }

    /* Exit the program */
    printf("Goodbye. \n\n");
    return EXIT_SUCCESS;
}
