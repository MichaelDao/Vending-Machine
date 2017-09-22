#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/

void initMenu(MenuItem * menu)
{
    printf("Main Menu:\n"
           "1. Display items\n"
           "2.Purchase Items\n"
           "3.Save and Exit\n"
           "Administrator-Only Menu:\n"
           "4.Add Item\n"
           "5.Remove Item\n"
           "6.Display Coins\n"
           "7.Reset Stock\n"
           "8.Reset Coins\n"
           "9.Abort Program\n"
           "Select your option (1-9): ");
}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem * menu)
{
    return NULL;
}
