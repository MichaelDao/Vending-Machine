/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <NULL>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm.h"
#define MENU_LENGTH 9


int main(int argc, char ** argv)
{
    /* Create structures for calling */
    MenuItem menu[MENU_LENGTH];
    VmSystem system;
    MenuFunction option;


    /* DEBUG SETTING IT UP MANUALLY */

    argv[1] = "stock.dat";
    argv[2] = "coins.dat";


    /* Initialize the system TODO Ensure boolean is used*/
    systemInit(&system);

    /* Load the files */
    loadData(&system, argv[1], argv[2]);

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

        if (option == saveAndExit)
            break;
        else if (option == NULL)
            continue;
        else
            (*option)(&system);
    }
}
