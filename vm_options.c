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

    killLinkedList(system->itemList->head);

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

    Stock * stock;
    /* delimiter */
    const char STOCK_DELIMIT[2] = "|";

    /* Store individual text */
    char *token;

    /* Allocate memory to Node and Stock */
    /*List *vendingList = malloc(sizeof(List));
*/

    /* Read the file TODO Instead of string name, try to use filename char */
    stockFile = fopen(fileName, "r");

    /* read each line in the text file */
    while (fgets(buff, sizeof(buff), stockFile))
    {
        stock = malloc(sizeof(Stock));

        /* Grab the whole line for processing */
        token = strtok(buff, STOCK_DELIMIT);

        /* Read the token */
        splitToken(token,stock);

        /* Create the node and update the itemList*/
        system->itemList = createNode(system->itemList, stock);

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

    printf("\nID    | Name%-16s | Available | Price\n", "");
    printf("---------------------------------------------\n");

    currentNode = system->itemList->head;

    while(currentNode != NULL)
    {
        printf("%s | ", currentNode->data->id);
        printf("%-20s | ", currentNode->data->name);
        printf("%-9d | ", currentNode->data->onHand);
        printf("$ %d.%02d\n", currentNode->data->price.dollars,
               currentNode->data->price.cents);

        /* Get the next node */
        currentNode = currentNode->next;
    }

    pressEnterToContinue();
}



/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem * system)
{
    char input[ID_LEN + EXTRA_SPACES];

    Node * purchaseItem = NULL;

    List * vendingList;
    vendingList = system->itemList;

    printf("\nPurchase Item\n");
    printf("----------------\n");

    for(;;)
    {
        printf("Please enter the ID of the item you would like to purchase: ");

        /* Take in user input */
        /*fgets(input, sizeof(input), stdin);
*/
        if(!checkInput(input))
            return;

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
               purchaseItem->data->price.dollars,
               purchaseItem->data->price.cents);

        printf("Please hand over the money – "
                       "type in the value of each note/coin in cents.\n"
                       "Press enter on a new and empty line "
                       "to cancel this purchase:\n");

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

    /* Prompt to exit */
    pressEnterToContinue();
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem * system)
{
    FILE * filePointer;
    char * fileName;
    Node * cursor;

    fileName = "stock.dat";
    filePointer = fopen(fileName, "w+");

    cursor = system->itemList->head;

    while(cursor != NULL)
    {
        fprintf(filePointer, "%s|", cursor->data->id);
        fprintf(filePointer, "%s|", cursor->data->name);
        fprintf(filePointer, "%s|", cursor->data->desc);
        fprintf(filePointer, "%d.%d|",
                cursor->data->price.dollars, cursor->data->price.dollars);
        fprintf(filePointer, "%d\n", cursor->data->onHand);




        /* Move to the next node */
        cursor = cursor->next;
    }

    fclose(filePointer);

    printf("Saved data to the file!");

   /* systemFree(system);
*/
    /* IM RUNNING INTO THE NINTH OPTION NOW */
    abortProgram(system);

}


/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem * system)
{
    /* Constants */
    const int MAX_PRICE_LEN = 4;
    const int BASE_10 = 10;
    const char * PRICE_DELIMIT = ".";

    /* All the input variables for fgets*/
    char uniqueId[ID_LEN + EXTRA_SPACES];
    char inputName[NAME_LEN + NULL_SPACE];
    char inputDesc[DESC_LEN + NULL_SPACE];
    char inputPrice[MAX_PRICE_LEN + EXTRA_SPACES];

    /* Products of the price delimiter */
    char * dollarExtract;
    char * centExtract;

    /* Variable that holds the integer of the delimit variables */
    unsigned dollarInt;
    unsigned centInt;

    /* Allocate memory to Node and Stock */
    List * vendingList; /* = malloc(sizeof(List));*/
    Stock * stock = malloc(sizeof(Stock));

    vendingList = system->itemList;

    /* Automatically generate a new ID */
    generateID(system->itemList, uniqueId);

    /* Update the stock node with the new ID */
    strcpy(stock->id, uniqueId);

    /* Print the value of the next uniqueID */
    printf("This new meal item will have the Item id of %s.\n", uniqueId);

    /* Record the input for Item Name */

    /* Take in item name input */
    printf("Enter the item name: ");
    /*fgets(inputName, sizeof(inputName), stdin);*/

    if(!checkInput(inputName))
    {

        return;
    }

    /* Complete the string for name */
    inputName[strlen(inputName) - 1] = '\0';

    /* Assign the name to the stock node */
    strcpy(stock->name, inputName);

    /* Record the input for Item Description */
    /* Take in item description via fgets */
    printf("Enter the item description: ");
    /*fgets(inputDesc, sizeof(inputDesc), stdin);*/

    if(!checkInput(inputDesc))
        return;

    /* complete string for description */
    inputDesc[strlen(inputDesc) - 1] = '\0';

    /* Assign description to stock node */
    strcpy(stock->desc, inputDesc);

    /* Record the input for Item price */
    for(;;)
    {
        /* Take in item price from user input */
        printf("Enter the price for this item: ");
        /*fgets(inputPrice, sizeof(inputPrice), stdin);*/

        if(!checkInput(inputPrice))
            return;

        /* Complete the input string */
        inputPrice[strlen(inputPrice) - 1] = '\0';

        /* If there is no decimal point, re enter input! */
        if (inputPrice[strlen(inputPrice) - 3] != *PRICE_DELIMIT)
        {
            printf("You are missing a decimal point (.), invalid price!\n");
            continue;
        }

        /* get dollars and cents from price as a string */
        dollarExtract = strtok(inputPrice, COIN_DELIM);
        centExtract = strtok(NULL, COIN_DELIM);

        /* Transform dollars and cents into an integer */
        dollarInt =  (unsigned) strtol(dollarExtract, NULL, BASE_10);
        centInt = (unsigned) strtol(centExtract, NULL, BASE_10);

        /* Re enter input if the cents is not a proper denomination */
        if (centInt % 5 != 0)
        {
            printf("No suitable change possible for %d cents!\n", centInt);
            continue;
        }

        /* Assign price in dollars and cents to stock */
        stock->price.dollars = dollarInt;
        stock->price.cents = centInt;

        /* Exit loop */
        break;
    }

    /* Assign default stock levels */
    stock->onHand = DEFAULT_STOCK_LEVEL;

    /* Create the node and update the itemList*/
    system->itemList = createNode(vendingList, stock);

    /* Confirm creation of node */
    printf("This item “%s, %s” has now been added to the menu.\n",
           inputName, inputDesc);

    /* Prompt to exit */
    pressEnterToContinue();
}

/* Generate the next ID in the linked list */
char * generateID(List * vendingList, char uniqueId[])
{
    /* index for loops */
    int x;

    /* How many zeroes exist in the code */
    unsigned noOfZeroes;

    /* This is the value of the next ID */
    int lastIDValue;
    char lastIDValueString[1 + NULL_SPACE];

    /* Get next value in the list for ID */
    lastIDValue = vendingList->size + 1;

    /* If the value is 1 digit, 3 zeroes*/
    if (lastIDValue >= 0 && lastIDValue < 10)
        noOfZeroes = 3;

        /* If the value is 2 digits, 2 zeroes*/
    else if (lastIDValue >= 10 && lastIDValue < 100)
        noOfZeroes = 2;

        /* If the value is 3 digits, 1 zeroes*/
    else if (lastIDValue >= 100 && lastIDValue < 1000)
        noOfZeroes = 1;

        /* If the value is 4 digits, no zeroes*/
    else
        noOfZeroes = 0;

    /* Place character 'I' in the first position of the address */
    strcpy(&uniqueId[0], "I");

    /* Print the exact amount of zeroes needed */
    for(x = 0; x < noOfZeroes; x++)
        strcat(uniqueId, "0");

    /* Convert the int to a string */
    sprintf(lastIDValueString, "%d", lastIDValue);

    /* Add the ID value onto the end of the string */
    strcat(uniqueId, lastIDValueString);

    /* Return it to the caller */
    return uniqueId;
}

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem * system)
{
    Node *targetNode = NULL;
    char input[ID_LEN + EXTRA_SPACES];
    List * vendingList;

    vendingList = system->itemList;

    for(;;)
    {
        printf("Enter the item id of the item to remove from the menu: ");

        if (!checkInput(input))
            return;

        /* Before passing the input, modify it */
        input[strlen(input) - 1] = '\0';

        targetNode = searchItemID(vendingList, input);

        if (targetNode == NULL)
        {
            printf("Could not find %s\n", input);
            continue;
        }
        else
        {
            removeNode(vendingList, targetNode);
        }
        break;
    }

    printf("\n%s has been removed!\n", input);

    /* Prompt to exit */
    pressEnterToContinue();

}

/**
 *
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem * system)
{
    printf("\nCoins has not been implemented yet!\n");

    /* Prompt to exit */
    pressEnterToContinue();

}

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem * system)
{
    Node * cursor = system->itemList->head;

    while(cursor != NULL)
    {
        cursor->data->onHand = DEFAULT_STOCK_LEVEL;
        cursor = cursor->next;
    }

    printf("All stock has been reset to the default level of %d\n",
           DEFAULT_STOCK_LEVEL);

    /* Prompt to exit */
    pressEnterToContinue();
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
    printf("\nCoins has not been implemented yet!\n");

    /* Prompt to exit */
    pressEnterToContinue();
}

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem * system)
{
    /*TODO You need to free up memory before leaving*/
    systemFree(system);

    /* Exit the program */
    printf("\nGoodbye. \n\n");
    exit(0);
}



void pressEnterToContinue()
{
    int myChar = 0;

    printf("\nPlease press ENTER to continue\n");

    while (myChar != '\r' && myChar  != '\n')
        myChar = getchar();


}


Boolean checkInput(char * input)
{
    for(;;)
    {
        /* Take in user input */
        fgets(input, sizeof(input), stdin);

        /* If nothing is entered, then return to menu */
        if (strcmp(input, "\n\0") == 0)
        {
            printf("\nReturning to the main menu!\n");
            return FALSE;
        }

            /* check buffer overflow */
        else if (input[strlen(input) - 1] != '\n')
        {
            printf("Wrong input, please try again!\n");
            readRestOfLine();
            continue;
        }
        return TRUE;
    }
}