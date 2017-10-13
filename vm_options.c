/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <13/10/2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm_options.h"

/*
 * vm_options.c contains the system handling functions
 * (e.g., init, free, load, save) and the main options.
 */

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

    /* It all checks out */
    return TRUE;
}

/**
 * Free all memory that has been allocated. Run with valgrind to find leaks
 **/
void systemFree(VmSystem * system)
{
    /* Delete the linked list before exiting */
    killLinkedList(system->itemList->head);

    /* Free the Linked list memory */
    free(system->itemList);
}

/**
 * Load stock and coin data into the system.
 **/
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName)
{
    /* Assign the file names to the system */
    system->stockFileName = stockFileName;
    system->coinFileName = coinsFileName;

    /* Load stock file */
    if(loadStock(system, system->stockFileName))
        return TRUE;

        /* Error in loading the file */
    else
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

    /* Create stock node */
    Stock * stock;

    /* delimiter */
    const char STOCK_DELIMIT[2] = "|";

    /* Store individual text */
    char *token;

    /* Read the file */
    stockFile = fopen(fileName, "r");

    /* read each line in the text file */
    while (fgets(buff, sizeof(buff), stockFile))
    {
        /* Allocate memory to the stock node */
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
    /* Create node */
    Node * currentNode;
    currentNode = system->itemList->head;

    /* Print menu header */
    printf("\nID    | Name%-16s | Available | Price\n", "");
    printf("---------------------------------------------\n");

    /* Loop through all nodes until the end */
    while(currentNode != NULL)
    {
        /* Print the details of each node */
        printf("%s | ", currentNode->data->id);
        printf("%-20s | ", currentNode->data->name);
        printf("%-9d | ", currentNode->data->onHand);
        printf("$ %d.%02d\n", currentNode->data->price.dollars,
               currentNode->data->price.cents);

        /* Get the next node */
        currentNode = currentNode->next;
    }

    /* Prompt to continue */
    pressEnterToContinue();
}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem * system)
{
    /* Input for ID */
    char input[ID_LEN + EXTRA_SPACES];

    /* This variable holds the node to be purchased */
    Node * purchaseItem = NULL;

    /* This will hold the Linked list */
    List * vendingList;
    vendingList = system->itemList;

    /* Print header */
    printf("\nPurchase Item\n");
    printf("----------------\n");

    /* Find the node with the ID */
    for(;;)
    {
        /* prompt */
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
        else if (input[strlen(input) - 1] != '\n')
        {
            printf("Wrong input, please try again!\n");
            readRestOfLine();
            continue;
        }

        /* Before passing the input, modify it */
        input[strlen(input) - 1] = '\0';

        /* Get the node with the ID */
        purchaseItem = searchItemID(vendingList, input);

        /* Re loop if ID does not exist */
        if (purchaseItem == NULL)
        {
            printf("Could not find %s\n", input);
            continue;
        }

        /* If this item is out of stock, reloop */
        if (purchaseItem->data->onHand == 0)
        {
            printf("This item is out of stock!\n");
            continue;
        }

        /* Display the node details in a prompt */
        printf("You have selected '%s %s' This will cost you $%d.%02d.\n",
               purchaseItem->data->name, purchaseItem->data->desc,
               purchaseItem->data->price.dollars,
               purchaseItem->data->price.cents);

        /* Provide instructions via prompt */
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
            /* If quitting, refund change and return to menu */
            return;

        /* Break out of loop */
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
        fprintf(filePointer, "%d.%.2d|",
                cursor->data->price.dollars, cursor->data->price.cents);
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
    /*const int MAX_PRICE_LEN = 4;
    */const int BASE_10 = 10;
    const char *PRICE_DELIMIT = ".";

    /* All the input variables for fgets*/
    char uniqueId[ID_LEN + EXTRA_SPACES];
    char inputName[NAME_LEN + EXTRA_SPACES];
    char inputDesc[DESC_LEN + EXTRA_SPACES];
    char inputPrice[4 + EXTRA_SPACES];

    /* Products of the price delimiter */
    char *dollarExtract;
    char *centExtract;

    /* Variable that holds the integer of the delimit variables */
    unsigned dollarInt;
    unsigned centInt;

    /* Allocate memory to Node and Stock */
    List *vendingList; /* = malloc(sizeof(List));*/
    Stock *stock = malloc(sizeof(Stock));

    /* Initialize vendingList to the system linked list */
    vendingList = system->itemList;

    /* Automatically generate a new ID */
    generateID(system->itemList, uniqueId);

    /* Update the stock node with the new ID */
    strcpy(stock->id, uniqueId);

    /* Print the value of the next uniqueID */
    printf("This new meal item will have the Item id of %s.\n", uniqueId);

    /* Record the input for Item Name */
    for (;;)
    {
        /* Take in item name input */
        printf("Enter the item name: ");

        /* Take in user input */
        fgets(inputName, sizeof(inputName), stdin);

        /* If nothing is entered, then return to menu */
        if (strcmp(inputName, "\n\0") == 0)
        {
            printf("\nReturning to the main menu!\n");
            return;
        }

            /* check buffer overflow */
        else if (inputName[strlen(inputName) - 1] != '\n')
        {
            printf("Wrong input, please try again!\n");
            readRestOfLine();
            continue;
        }

        /* Complete the string for name */
        inputName[strlen(inputName) - 1] = '\0';

        /* Assign the name to the stock node */
        strcpy(stock->name, inputName);

        /* Move on */
        break;
    }

    /* Record the input for Item Description */
    for (;;)
    {
        /* Take in item description via fgets */
        printf("Enter the item description: ");

        /* Take in user input */
        fgets(inputDesc, sizeof(inputDesc), stdin);

        /* If nothing is entered, then return to menu */
        if (strcmp(inputDesc, "\n\0") == 0)
        {
            printf("\nReturning to the main menu!\n");
            return;
        }

            /* check buffer overflow */
        else if (inputDesc[strlen(inputDesc) - 1] != '\n')
        {
            printf("Wrong input, please try again!\n");
            readRestOfLine();
            continue;
        }

        /* complete string for description */
        inputDesc[strlen(inputDesc) - 1] = '\0';

        /* Assign description to stock node */
        strcpy(stock->desc, inputDesc);

        /* Move on */
        break;
    }

    /* Record the input for Item price */
    for(;;)
    {
        /* Take in item price from user input */
        printf("Enter the price for this item: ");

        /* Take in user input */
        fgets(inputPrice, sizeof(inputPrice), stdin);

        /* If nothing is entered, then return to menu */
        if (strcmp(inputPrice, "\n\0") == 0)
        {
            printf("\nReturning to the main menu!\n");
            return;
        }

            /* check buffer overflow */
        else if (inputPrice[strlen(inputPrice) - 1] != '\n')
        {
            printf("Wrong input, please try again!\n");
            readRestOfLine();
            continue;
        }

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
    printf("\nThis item “%s, %s” has now been added to the menu.\n",
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

    /* Initialize List */
    List * vendingList;
    vendingList = system->itemList;

    /* Begin loop to remove node */
    for(;;)
    {
        /* prompt */
        printf("Enter the item id of the item to remove from the menu: ");

        /* Take in user input */
        fgets(input, sizeof(input), stdin);

        /* If nothing is entered, then return to menu */
        if (strcmp(input, "\n\0") == 0)
        {
            printf("\nReturning to the main menu!\n");
            return;
        }

            /* check buffer overflow */
        else if (input[strlen(input) - 1] != '\n')
        {
            printf("Wrong input, please try again!\n");
            readRestOfLine();
            continue;
        }

        /* Before passing the input, modify it */
        input[strlen(input) - 1] = '\0';

        /* get the node to delete */
        targetNode = searchItemID(vendingList, input);

        /* Repeat if node could not be found */
        if (targetNode == NULL)
        {
            printf("Could not find %s\n", input);
            continue;
        }

        /* Remove the node if found */
        removeNode(vendingList, targetNode);

        /* exit loop */
        break;
    }

    /* prompt */
    printf("\n%s has been removed!\n", input);

    /* Prompt to exit */
    pressEnterToContinue();
}

/**
 * This option will display the coins from lowest to highest value and
 * correctly align them. This function implements part 4 of requirement 18
 * in the assignment specifications.
 **/
void displayCoins(VmSystem * system)
{
    printf("\nCoins has not been implemented yet!\n");

    /* Prompt to exit */
    pressEnterToContinue();
}

/**
 * This option will iterate over every stock in the list and set its
 * onHand count to the default value specified in the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem * system)
{
    /* Initialize node to the head node */
    Node * cursor = system->itemList->head;

    /* loop through each node in the linked list and reset stock levels */
    while(cursor != NULL)
    {
        cursor->data->onHand = DEFAULT_STOCK_LEVEL;
        cursor = cursor->next;
    }

    /* prompt */
    printf("All stock has been reset to the default level of %d\n",
           DEFAULT_STOCK_LEVEL);

    /* Prompt to exit */
    pressEnterToContinue();
}

/**
 * This option will iterate over every coin in the coin list and set
 * its 'count' to the default value specified.
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
 * This option will display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem * system)
{
    /* Free up the system memory */
    systemFree(system);

    /* Exit the program */
    printf("\nGoodbye. \n\n");
    exit(0);
}

/* This helps the program pause before returning to the menu */
void pressEnterToContinue()
{
    /* setup variable */
    int enterToContinue = 0;

    /* prompt */
    printf("\nPlease press ENTER to continue\n");

    /* press enter on anything to continue */
    while (enterToContinue != '\r' && enterToContinue  != '\n')
        enterToContinue = getchar();
}