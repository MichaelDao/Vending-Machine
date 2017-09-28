/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <NULL>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */

/* Initialize the list */
List* initializeList()
{
    /* Allocate memory to list */
    List* vendingList = malloc(sizeof(vendingList));

    /* exit if vmList doesnt exist */
    if (vendingList == NULL)
        exit(EXIT_FAILURE);

    else
    {/* Assign default values */
        vendingList->head = NULL;
        vendingList->size = 0;
    }

    /* Return the initialized list */
    return vendingList;
}


/* Create a new node before applying data */
Node* createNode(List *vendingList, Stock *data)
{
    Node * previousNode;
    Node * currentNode;

    Node* newNode = malloc(sizeof(newNode));

    if(newNode == NULL)
    {
        printf("Error creating node");
        exit(0);
    }

    /* Allocate memory to the newNode */
    newNode->data = malloc(sizeof(*newNode->data));

    if(newNode->data == NULL)
    {
        free(newNode);
        printf("Error creating node");
        exit(0);
    }

    /* Apply the data to the newNode */
    *newNode->data = *data;

    previousNode = NULL;

    currentNode = vendingList->head;


    /* Only when there is a head */
    while(currentNode != NULL)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    /* When there is no head, assign the head node */
    if(vendingList->head == NULL)
        vendingList->head = newNode;

    else if(previousNode == NULL)
    {
        /* Inserting at the head. */
        newNode->next = vendingList->head;
        vendingList->head = newNode;
    }
    else
    {
        previousNode->next = newNode;
        newNode->next = currentNode;
    }

    /* Increment the size integer */
    vendingList->size++;

    return vendingList;
}

void splitToken(char *token, Stock *stock)
{


    /* strol pointer */
    char *ptr;
    /* Holds strol result */
    unsigned stringConvert;
    const char delimit[2] = "|";

    /* For loop index */
    int x;

    /* walk through all tokens */
    for(x=0; token != NULL; x++ )
    {
        switch (x)
        {
            case 0:
                strcpy(stock->id, token);
                break;
            case 1:
                strcpy(stock->name, token);
                break;
            case 2:
                strcpy(stock->desc, token);
                break;
            case 3:
                stringConvert = (unsigned)strtol(token, &ptr, 0);
                stock->price.dollars = stringConvert;
                break;
            case 4:
                stringConvert = (unsigned)strtol(token, &ptr, 0);
                stock->onHand = stringConvert;
                break;
            default :
                printf("default");
        }

        /* move to the next token */
        token = strtok(NULL, delimit);
    }
}