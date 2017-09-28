/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <NULL>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm_coin.h"

/**
 * Implement functions here for managing coins and the
 * "cash register" contained in the VmSystem struct.
 **/

/**
 * Some example functions:
 * init coins array, insert coin, change coin count for Denomination,
 * convert Denomination to coin value, deducting coins from register, etc...
 */

Coin* initializeCoins(Coin * cashRegister)
{
    Denomination value = FIVE_CENTS;
    int x;

    for (x = 0; x < NUM_DENOMS; x++)
    {
        /* Apply the denomination enum */
        cashRegister[x].denom = value;

        /* Apply the default coin count */
        cashRegister[x].count = DEFAULT_COIN_COUNT;

        /* Increment the denomination */
        value++;
    }
}