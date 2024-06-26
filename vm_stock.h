/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <13/10/2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when resetting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"

Node * removeFront(Node * vendingList);
Node * removeBack(Node * cursor);

#endif