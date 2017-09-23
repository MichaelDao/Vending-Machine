#include "vm_options.h"

/**
 * vm_options.c this is where you need to implement the system handling
 * functions (e.g., init, free, load, save) and the main options for
 * your program. You may however have some of the actual work done
 * in functions defined elsewhere.
 **/

/**
 * Initialise the system to a known safe state. Look at the structure
 * defined in vm_system.h.
 **/
Boolean systemInit(VmSystem * system)
{

    return FALSE;
}

/**
 * Free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind.
 **/
void systemFree(VmSystem * system)
{ }

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName)
{
    /* Load stock file */
    loadStock(system, stockFileName);

    return FALSE;
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem * system, const char * fileName)
{
    FILE *filePoint; /* File reader pointer */

    char buff[255]; /* Store text line */
    char *token; /* Store seperated text */
    const char delimit[2] = "|"; /* delimiter */

    Node *head = NULL;
    Node *tmp = NULL;

    Node *next;
    Stock *data;

    char *ptr; /* strol pointer */
    int stringConvert; /* Holds strol result */

    int x; /* for loop index */

    /* Read the file */
    /* TODO Instead of string name, try to use filename char */
    filePoint = fopen("stock.dat", "r");

    /* DEBUG NEW LINE */
    printf("\n");
/*
    prepareNode(head, data);
*/
    /* read each line */
    while (fgets(buff, sizeof(buff), filePoint))
    {
        /* Grab the whole string line to be processed */
        token = strtok(buff, delimit);

        /* walk through all tokens */
        for(x=0; token != NULL; x++ ) {
            switch (x) {
                case 0:
                    strcpy(data->id, token);
                    break;
                case 1:
                    strcpy(data->name, token);
                    break;
                case 2:
                    strcpy(data->desc, token);
                    break;
                case 3:
                    stringConvert = strtol(token, &ptr, 0);
                    data->price.dollars = stringConvert;
                    break;
                case 4:
                    stringConvert = strtol(token, &ptr, 0);
                    data->onHand = stringConvert;
                    break;
            }

            /* Debug print the token */
            printf( " %s\n", token );

            /* move to the next token */
            token = strtok(NULL, delimit);
        }
/*
        head = createNode(data,next);
  */      printf("==========================\n");
    }

    /* Close the file reader */
    fclose(filePoint);
    return FALSE;
}

/* Create a new node before applying data */
Node* createNode(Stock *data, Node *next)
{
    Node* newNode = malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = next;

    return newNode;
}

/* Point to the new node in the list */
Node* prepareNode(Node *head, Stock *data)
{
    /* Call create node method */
    Node* newNode = createNode(data, head);

    /* The head will be set to this node */
    head = newNode;
    return head;
}




/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem * system, const char * fileName)
{
    /* pointer for file reading */
    FILE *fileRead;

    /* For text file buffer size */
    char buff[255];

    /* Read the file */
    fileRead = fopen(fileName, "r");

    /* Line 1 */
    fgets(buff, sizeof(buff), fileRead);
    printf("1: %s\n", buff);

    /* Line 2 */
    fgets(buff, sizeof(buff), fileRead);
    printf("2: %s\n", buff);

    /* Close the file reader */
    fclose(fileRead);

    return FALSE;

    /* Write to file */
    /*
    fp = fopen("stock.dat", "w+");
    fprintf(fp, "THIS IS TEST\n");
    fputs("yes\n",fp);
    fclose(fp);
    */
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

    Node * headNode;

    printf("DEBUG\n");

    printf("ID \t | Name \t\t | Available | Price\n");
    printf("---------------------------------------------");

/*
    quickLookList(headNode);
*/

}

/*
    traverse the linked list
*/
void quickLookList(Node * headNode)
{
    Node* currentNode;
    currentNode = headNode;
    while(currentNode != NULL)
    {
        if (currentNode != NULL)
            printf("%s ", currentNode->data->id);

        /* Get the next node */
        currentNode = currentNode->next;
    }
}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem * system)
{


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
