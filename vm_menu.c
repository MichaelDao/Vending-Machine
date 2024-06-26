/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <13/10/2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * Initialise the array of menu items, this array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/

/*
 * Initialize the array of menu items to be displayed for the menu
 * This array of MenuItem will point to a function that will be called
 */
void initMenu(MenuItem * menu)
{
    /* initialize menu text */
    strcpy(menu[0].text, "1. Display Items");
    strcpy(menu[1].text, "2. Purchase Items");
    strcpy(menu[2].text, "3. Save and Exit");
    strcpy(menu[3].text, "4. Add Item");
    strcpy(menu[4].text, "5. Remove Item");
    strcpy(menu[5].text, "6. Display Coins");
    strcpy(menu[6].text, "7. Reset Stocks");
    strcpy(menu[7].text, "8. Reset Coins");
    strcpy(menu[8].text, "9. Abort Program");

    /* Initialize index to functions */
    menu[0].function = displayItems;
    menu[1].function = purchaseItem;
    menu[2].function = saveAndExit;
    menu[3].function = addItem;
    menu[4].function = removeItem;
    menu[5].function = displayCoins;
    menu[6].function = resetStock;
    menu[7].function = resetCoins;
    menu[8].function = abortProgram;
}

/*
 * Get input from the user and return a pointer to the MenuFunction
 * to perform the user's selection.
 * NULL is returned if an invalid option is entered.
 */
MenuFunction getMenuChoice(MenuItem * menu)
{
    char input[1 + EXTRA_SPACES];
    int chosenOption;
    int base_10 = 10;

    /* print out the menu */
    printMenu(menu);

    for(;;)
    {
        /* Take in user input */
        printf("Select your option (1-9): ");
        fgets(input, sizeof(input), stdin);

        /* check buffer overflow */
        if (input[strlen(input) - 1] != '\n')
        {
            printf("Wrong input, please try again!\n");
            readRestOfLine();
            continue;
        }

        /* Transform char into an int */
        chosenOption = (int)strtol(input, NULL, base_10);

        /* As long as input is valid, call chosen function */
        if (chosenOption > 0 && chosenOption <= 9)
            return menu[chosenOption - 1].function;
        else
            return NULL;
    }
}

/*
 * Print out all the menu options to the console
 */
void printMenu(MenuItem * menu)
{
    int x;

    /* Loop and print all the menu text options */
    for(x = 0; x <= sizeof(menu); x++)
    {
        /* User menu only */
        if (x == 0)
            printf("\nMain Menu:\n");

            /* Admin only menu */
        else if (x == 3)
            printf("\nAdministrator-Only Menu:\n");

        /* Print each loop */
        printf("%s\n", menu[x].text);
    }
}