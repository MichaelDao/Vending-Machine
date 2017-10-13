/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <13/10/2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm_stock.h"

/**
 * vm_stock.c this is the file where the interface functions for managing
 * the stock list is implemented.
 **/

/* Initialize the list */
List* initializeList()
{
    /* Allocate memory to list */
    List* vendingList = malloc(sizeof(List));

    /* exit if vmList doesnt exist */
    if (vendingList == NULL)
        exit(EXIT_FAILURE);

    else
    {/* Assign default values */
        vendingList->head = NULL;
        vendingList->size = (unsigned)0;
    }

    /* Return the initialized list */
    return vendingList;
}

/* Create a new node before applying data */
List* createNode(List *vendingList, Stock *data)
{
    /* Setup Node variables */
    Node * previousNode;
    Node * currentNode;

    /* Assign memory to newNode */
    Node* newNode = malloc(sizeof(Node));

    /* Initialize each node */
    previousNode = NULL;
    currentNode = vendingList->head;

    /* Assign and hold the data in a node */
    newNode->data = data;

    /* Loop only when there is a head */
    while(currentNode != NULL)
    {
        /* Organize all the nodes into the linked list alphabetically */
        if(strcmp(newNode->data->name, currentNode->data->name) < 0)
            break;

        /* Hold value of head or node */
        previousNode = currentNode;

        /* Focus the current node to the next in the linked list */
        currentNode = currentNode->next;
    }

    /* When there is no head, there is no linked list assign only the head */
    if(vendingList->head == NULL)
        vendingList->head = newNode;

        /* Insert node at the head */
    else if(previousNode == NULL)
    {
        /* Attach the linked list to the end of new node */
        newNode->next = vendingList->head;

        /* This new combination is the now the linked list */
        vendingList->head = newNode;
    }

        /* Placing a node anywhere in the middle */
    else
    {
        /* Previous node will hold the new Node next */
        previousNode->next = newNode;

        /* Then attach the rest of the node after the new Node */
        newNode->next = currentNode;
    }

    /* Increment the size integer for each new node*/
    vendingList->size++;

    /* return the linked list */
    return vendingList;
}

/* Split the token from the save file when reading */
void splitToken(char *token, Stock *stock)
{
    const int BASE_10 = 10;

    /* loop index */
    int x;

    /* Variables for extracting the price into dollars and cents */
    char * priceExtract;
    char * dollarExtract;
    char * centExtract;
    char * onHandExtract;

    /* walk through all tokens */
    for (x = 0; token != NULL; x++)
    {
        /* Switch statement checks which data needs to be processed */
        switch (x)
        {
            /* Process ID */
            case 0:
                strcpy(stock->id, token);
                break;

                /* Process Name */
            case 1:
                strcpy(stock->name, token);
                break;

                /* Process description */
            case 2:
                strcpy(stock->desc, token);
                break;

                /* Process price and stock */
            case 3:
                /* save the price and onHand values first from the file */
                priceExtract = token;
                onHandExtract = strtok(NULL, STOCK_DELIM);

                /* extract dollars and cents from price token as string */
                dollarExtract = strtok(priceExtract, COIN_DELIM);
                centExtract = strtok(NULL, COIN_DELIM);

                /* Assign price in dollars and cents to stock */
                stock->price.dollars =
                        (unsigned) strtol(dollarExtract, NULL, BASE_10);
                stock->price.cents =
                        (unsigned) strtol(centExtract, NULL, BASE_10);

                /* Assign the onHand value */
                stock->onHand = (unsigned) strtol(onHandExtract, NULL, BASE_10);
                break;

            default :
                break;
        }

        /* move to the next token */
        token = strtok(NULL, STOCK_DELIM);
    }
}

/* Look for the correct ID in the linked list */
Node * searchItemID(List * vendingList, char * input)
{
    /* Initialize the node */
    Node * cursor = vendingList->head;

    /* Loop through all available nodes in the linked list */
    while(cursor != NULL)
    {
        /* If user input matches the node ID, return node */
        if(strcmp(cursor->data->id, input) == 0)
            return cursor;

        /* Focus on the next node in the linked list */
        cursor = cursor->next;
    }
    /* Could not find it */
    return NULL;
}

/* Delete a node from the linked list */
Node * removeNode(List * vendingList, Node * targetNode)
{
    /* Initialize this node just in case we have to remove the middle node */
    Node * middleNode;
    middleNode = vendingList->head;

    /* If it is the first node, remove the head */
    if (vendingList->head == targetNode)
    {
        /* Call removeFront function to remove head node */
        vendingList->head = removeFront(vendingList->head);
        return vendingList->head;
    }

    /* If last node in list, remove the end */
    if (targetNode->next == NULL)
    {
        /* Call removeBack function to remove the last node */
        vendingList->head = removeBack(vendingList->head);
        return vendingList->head;
    }

    /* If it is neither the front or back node, remove the node from the list */
    while (middleNode != NULL)
    {
        /* step through each node until the target has been found */
        if (middleNode->next == targetNode)
            break;

        /* focus on the next node in the list */
        middleNode = middleNode-> next;
    }

    /* If the middle node has been found */
    if(middleNode != NULL)
    {
        /* The temp Node will point at the node to remove */
        Node * tempNode = middleNode->next;

        /* Now attach the node after temp to the node before temp */
        middleNode->next = tempNode->next;

        /* Now remove the tempNode */
        tempNode->next = NULL;
    }

    /* Free memory */
    free(middleNode);

    /* Return the nodes at the head to caller */
    return vendingList->head;
}

/* Remove the node at the head */
Node * removeFront(Node * head)
{
    /* Point at node to remove */
    Node * targetNode = head;

    /* Point head at the next node */
    head = head->next;

    /* Remove the Node after the head */
    targetNode->next = NULL;

    /* Check if this is the only node in the list */
    if (targetNode == head)
        head = NULL;

    /* free memory */
    free(head);

    /* return the new head node */
    return head;
}

/* Remove the last node in the linked list */
Node * removeBack(Node * targetNode)
{
    /* Declare two Nodes to track this process */
    Node * tempNode = targetNode;
    Node * back = NULL;

    /* Start from the first node until it reaches the last */
    while (tempNode->next != NULL)
    {
        back = tempNode;
        tempNode = tempNode -> next;
    }

    /* Set the back pointer towards the null at the end */
    if (back != NULL)
        back->next = NULL;

    /* If this is the only node, then just simply remove it */
    if (tempNode == targetNode)
        targetNode = NULL;

    /* Free memory */
    free (tempNode);

    /* return the new node to the caller */
    return targetNode;
}

/* Delete the whole linked list to clear up memory */
void killLinkedList(Node * head)
{
    Node *tempNode;
    Node *targetNode;

    /* If the head exists */
    if (head != NULL)
    {
        /* Target node will focus on the next node */
        targetNode = head->next;

        /* Delete the node */
        head->next = NULL;

        /* While targetNode has not reached the end */
        while(targetNode != NULL)
        {
            /* Point at the next node in the list */
            tempNode = targetNode->next;

            /* free up the memory from the node including its data */
            free(targetNode->data);
            free(targetNode);

            /* Swap the variables, keep traversing down the list */
            targetNode = tempNode;
        }
    }
}