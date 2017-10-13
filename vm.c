/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <13/10/2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm.h"
#define MENU_LENGTH 9

int main(int argc, char ** argv)
{
    MenuItem menu[MENU_LENGTH];
    MenuFunction option;
    VmSystem system;

    /* DEBUG Uncomment for CLion */
    /*argv[1] = "stock.dat";
    argv[2] = "coins.dat";
    */

    /* Initialize the system */
    if(!systemInit(&system))
    {
        /* Error if returns false */
        printf("Error initializing system.");
        exit(0);
    }

    /* Load the files */
    loadData(&system, argv[1], argv[2]);

    /* Handle error if no stock file entered */
    if (system.stockFileName == NULL)
    {
        printf("\nError: file not found\n\n");
        exit(0);
    }

    /* Load stock file */
    loadStock(&system, system.stockFileName);

    /* Initialize menu */
    initMenu(menu);

    for(;;)
    {
        /* Print menu and ask for choice */
        option = getMenuChoice(menu);

        /* If option input is not wrong, call function */
        if (option != NULL)
            (*option)(&system);

        else
        {
            /* If returned NULL, loop menu again */
            printf("\nInvalid input, please try again\n");
            continue;
        }
    }
}
