/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <NULL>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm_options.h"

/**
 * vm_options.c this is where you need to implement the system handling
 * functions (e.g., init, free, load, save) and the main options for
 * your program. You may however have some of the actual work done
 * in functions defined elsewhere.
 **/

/**
 * Initialise the system to a known safe state.
 **/
Boolean systemInit(VmSystem * system)
{
    /* Initialize the coin */
    initializeCoins(system->cashRegister);

    /* Initialize the linked list */
    system->itemList = initializeList();

    /* Initialize the file names */
    system->coinFileName = NULL;
    system->stockFileName = NULL;

    return TRUE;
}

/**
 * Free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind.
 **/
void systemFree(VmSystem * system)
{
    free(system->itemList);
}

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName)
{
    system->stockFileName = stockFileName;
    system->coinFileName = coinsFileName;
    return FALSE;
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem * system, const char * fileName)
{
    /* text file pointer */
    FILE *stockFile;

    /* Store text line */
    char buff[DESC_LEN];

    /* delimiter */
    const char delimit[2] = "|";

    /* Store individual text */
    char *token;


    /* Allocate memory to Node and Stock */
    List *vendingList = malloc(sizeof(List));

    Stock *stock = malloc(sizeof(Stock));

    /* Read the file TODO Instead of string name, try to use filename char */
    stockFile = fopen(fileName, "r");

    /* read each line in the text file */
    while (fgets(buff, sizeof(buff), stockFile))
    {
        /* Grab the whole line for processing */
        token = strtok(buff, delimit);

        /* Read the token */
        splitToken(token,stock);

        /* Create the node and update the itemList*/
        system->itemList = createNode(vendingList, stock);
    }


    /* Close the file reader */
    fclose(stockFile);

    return FALSE;
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem * system, const char * fileName)
{
    return FALSE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem * system)
{
    return FALSE;
}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem * system)
{
    return FALSE;
}

/**
 * This option allows the user to display the items in the system.
 * This is the data loaded into the linked list in the requirement 2.
 **/
void displayItems(VmSystem * system)
{
    Node * currentNode;

    printf("\nID    | Name | Available | Price\n");
    printf("---------------------------------------------\n");


    currentNode = system->itemList->head;

    while(currentNode != NULL)
    {
        printf("%s | ", currentNode->data->id);
        printf("%s | ", currentNode->data->name);
        printf("%d \t\t | ", currentNode->data->onHand);
        printf("$ %d.%02d\n", currentNode->data->price.dollars,
               currentNode->data->price.cents);


        /* Get the next node */
        currentNode = currentNode->next;
    }

    pressEnterToContinue();
}

void pressEnterToContinue()
{
    int myChar = 0;

    printf("\nPlease press ENTER to continue\n");

    while (myChar != '\r' && myChar  != '\n')
        myChar = getchar();
}


/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem * system)
{
    char input[ID_LEN + EXTRA_SPACES];

    Node * purchaseItem = NULL;

    List * vendingList = system->itemList;

    printf("\nPurchase Item\n");
    printf("----------------\n");

    for(;;)
    {
        printf("Please enter the ID of the item you would like to purchase: ");

        /* Take in user input */
        fgets(input, sizeof(input), stdin);

        /* If nothing is entered, then return to menu */
        if (strcmp(input, "\n\0") == 0)
        {
            printf("\nReturning to the main menu!\n");
            return;
        }

        /* check buffer overflow */
        if (input[strlen(input) - 1] != '\n')
        {
            printf("Wrong input, please try again!\n");
            readRestOfLine();
            continue;
        }

        /* Before passing the input, modify it */
        input[strlen(input) - 1] = '\0';

        /* TODO IF THERE IS NO STOCK LEFT DONT DO IT*/
        purchaseItem = searchItemID(vendingList, input);

        if (purchaseItem == NULL)
        {
            printf("Could not find %s\n", input);
            continue;
        }

        printf("You have selected '%s %s' This will cost you $%d.%02d.\n",
               purchaseItem->data->name, purchaseItem->data->desc,
               purchaseItem->data->price.dollars, purchaseItem->data->price.cents);

        printf("Please hand over the money – type in the value of each note/coin in cents.\n"
               "Press enter on a new and empty line to cancel this purchase:\n");

        /* If the item is purchased, update stock */
        if (insertMoney(purchaseItem))
        {
            purchaseItem->data->onHand--;
            printf("Please come back soon.\n");
        }
        else
            /* refund and return to menu */
            return;

        break;
    }
}

Boolean insertMoney(Node * purchaseItem)
{
    char input[ID_LEN + EXTRA_SPACES];

    int base_10 = 10;
    unsigned price;

    int remainingDollars;
    int remainingCents;

    unsigned dollarExtract;
    unsigned centExtract;

    unsigned dollarTotal;
    unsigned centTotal;

    dollarTotal = 0;
    centTotal = 0;

    /* Setup temporary variables */
    remainingDollars = purchaseItem->data->price.dollars;
    remainingCents = purchaseItem->data->price.cents;

    for (;;)
    {
        printf("You still need to give us $%d.%02d: ",
               remainingDollars, remainingCents);

        /* Take in user input */
        fgets(input, sizeof(input), stdin);

        /* If nothing is entered, return change and go back to the menu */
        if (strcmp(input, "\n\0") == 0)
        {
            printf("\nReturning your money at a value of $%d.%02d\n",
                   dollarTotal, centTotal);
            return FALSE;
        }

        /* check buffer overflow */
        if (input[strlen(input) - 1] != '\n')
        {
            printf("Wrong input, please try again!\n");
            readRestOfLine();
            continue;
        }

        /* Convert the input to an integer */
        price = (unsigned) strtol(input, NULL, base_10);

        dollarExtract = price / 100;
        centExtract = price % 100;

        if (price == 0)
        {
            printf("Error: Please enter a valid denomination\n");
            continue;
        }
        else if (price == 5 || price == 10 || price == 20 || price == 50 ||
                price == 100 || price == 200 || price == 500 || price == 1000)
        {
            /* Add on the running total */
            dollarTotal += dollarExtract;
            centTotal += centExtract;

            /* Subtract the remaining value */
            remainingDollars -= dollarExtract;
            remainingCents -= centExtract;

            if (remainingDollars == 0 )
            {
                printf("Thank you. Here is your %s.\n",
                       purchaseItem->data->name);
                return TRUE;

            }
            else if (remainingDollars < 0 )
            {
                /* Calculate the change owed and return it */
                printf("\nThank you. Here is your %s, and your change of $%d.%02d.\n",
                purchaseItem->data->name, abs(remainingDollars) - 1, 100 - remainingCents );
                return TRUE;
            }
            else
                /* Reloop for remaining value needed */
                continue;
        }
        else
        {
            printf("Error: $%d.%02d is not a valid denomination of money.\n", dollarExtract, centExtract);
            continue;
        }
    }
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem * system)
{

}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem * system)
{



}

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem * system)
{



}

/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem * system)
{



}

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem * system)
{



}

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code.
 * This requirement implements part 3 of requirement 18 in the
 * assignment specifications.
 **/
void resetCoins(VmSystem * system)
{



}

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem * system)
{


}