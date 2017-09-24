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
Node* createNode(Node *next, Stock *data)
{
    Node* newNode = malloc(sizeof(Node));

    if(newNode == NULL)
    {
        printf("Error creating node");
        exit(0);
    }

    newNode->data = data;
    newNode->next = next;

    return newNode;
}

Node* prepareNode(Node *head, Stock *data)
{
    /* Call create node method */
    Node* newNode = createNode(head, data);

    /* The head will be set to this node */
    head = newNode;
    return head;
}

void traverseList(Node * headNode)
{
    Node* currentNode = currentNode = headNode;

    while(currentNode != NULL)
    {
        printf("%s ", currentNode->data->id);

        /* Get the next node */
        currentNode = currentNode->next;
    }
}