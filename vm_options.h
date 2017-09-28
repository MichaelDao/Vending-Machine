/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <NULL>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#ifndef VM_OPTIONS_H
#define VM_OPTIONS_H

#include "vm_stock.h"

Boolean systemInit(VmSystem * system);
void systemFree(VmSystem * system);
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName);
Boolean loadStock(VmSystem * system, const char * fileName);
Boolean loadCoins(VmSystem * system, const char * fileName);
Boolean saveStock(VmSystem * system);
Boolean saveCoins(VmSystem * system);

void displayItems(VmSystem * system);
void purchaseItem(VmSystem * system);
void saveAndExit(VmSystem * system);
void addItem(VmSystem * system);
void removeItem(VmSystem * system);
void displayCoins(VmSystem * system);
void resetStock(VmSystem * system);
void resetCoins(VmSystem * system);
void abortProgram(VmSystem * system);

List* initializeList();

Node* createNode(Stock *data, Node *next);
Node* prepareNode(Node *head, Stock *data);
void traverseList(Node * headNode);
void splitToken(char *token, Stock *stock);

#endif
