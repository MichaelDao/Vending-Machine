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
List* createNode(List *vendingList, Stock *data)
{
    Node * previousNode;
    Node * currentNode;

    Node* newNode = malloc(sizeof(newNode));

    if(newNode == NULL)
    {
        printf("Error creating node");
        return NULL;
    }

    /* Allocate memory to the newNode */
    newNode->data = malloc(sizeof(*newNode->data));

    if(newNode->data == NULL)
    {
        free(newNode);
        printf("Error creating node");
        return NULL;
    }

    /* Apply the data to the newNode */
    *newNode->data = *data;

    previousNode = NULL;

    currentNode = vendingList->head;

    /*  when there is a head */
    while(currentNode != NULL)
    {
        if(strcmp(newNode->data->name, currentNode->data->name) < 0)
        {
            break;
        }

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
    /* Holds strol result */

    const int base_10 = 10;

    /* For loop index */
    int x;

    char * priceExtract;

    char * dollarExtract;
    char * centExtract;

    char * onHandExtract;


    /* walk through all tokens */
    for (x = 0; token != NULL; x++)
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
                /* save the price and onHnad values */
                priceExtract = token;
                onHandExtract = strtok(NULL, STOCK_DELIM);

                /* get dollars and cents from price as a string */
                dollarExtract = strtok(priceExtract, ".");
                centExtract = strtok(NULL, ".");

                /* Assign price in dollars and cents to stock */
                stock->price.dollars = (unsigned) strtol(dollarExtract, NULL, base_10);
                stock->price.cents = (unsigned) strtol(centExtract, NULL, base_10);

                /* Assign the onHand value */
                stock->onHand = (unsigned) strtol(onHandExtract, NULL, base_10);

                break;

            default :
                printf("default");
        }

        /* move to the next token */
        token = strtok(NULL, STOCK_DELIM);
    }
}

Node * searchItemID(List * vendingList, char * input)
{
    Node * cursor = vendingList->head;

    while(cursor != NULL)
    {

        if(strcmp(cursor->data->id, input) == 0)
            return cursor;

        cursor = cursor->next;
    }
    return NULL;
}