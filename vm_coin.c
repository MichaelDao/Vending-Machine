/******************************************************************************

** Student Name: <Michael Dao>

** Student Number: <s3668300>

** Date of submission: <13/10/2017>

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
    int x;
    Denomination value = FIVE_CENTS;

    for (x = 0; x < NUM_DENOMS; x++)
    {
        /* Apply the default coin count */
        cashRegister[x].count = DEFAULT_COIN_COUNT;

        /* Apply the denomination and increment */
        cashRegister[x].denom = value++;
    }
    return NULL;
}

/*
 * An extension of the purchase movie
 */
Boolean insertMoney(Node * purchaseItem)
{
    char input[ID_LEN + EXTRA_SPACES];

    int base_10 = 10;
    unsigned price;

    int remainingDollars;
    int remainingCents;

    unsigned dollarExtract;
    unsigned centExtract;

    unsigned dollarTotal;
    unsigned centTotal;

    dollarTotal = 0;
    centTotal = 0;

    /* Setup temporary variables */
    remainingDollars = purchaseItem->data->price.dollars;
    remainingCents = purchaseItem->data->price.cents;

    for (;;)
    {
        printf("You still need to give us $%d.%02d: ",
               remainingDollars, remainingCents);

        /* Take in user input */
        fgets(input, sizeof(input), stdin);

        /* If nothing is entered, return change and go back to the menu */
        if (strcmp(input, "\n\0") == 0)
        {
            printf("\nReturning your money at a value of $%d.%02d\n",
                   dollarTotal, centTotal);
            return FALSE;
        }

        /* check buffer overflow */
        if (input[strlen(input) - 1] != '\n')
        {
            printf("Wrong input, please try again!\n");
            readRestOfLine();
            continue;
        }

        /* Convert the input to an integer */
        price = (unsigned) strtol(input, NULL, base_10);

        dollarExtract = price / 100;
        centExtract = price % 100;

        if (price == 0)
        {
            printf("Error: Please enter a valid denomination\n");
            continue;
        }
        else if (price == 5 || price == 10 || price == 20 || price == 50 ||
                 price == 100 || price == 200 || price == 500 || price == 1000)
        {
            /* Add on the running total */
            dollarTotal += dollarExtract;
            centTotal += centExtract;

            /* Subtract the remaining value */
            remainingDollars -= dollarExtract;
            remainingCents -= centExtract;

            if (remainingDollars == 0 )
            {
                printf("Thank you. Here is your %s.\n",
                       purchaseItem->data->name);
                return TRUE;

            }
            else if (remainingDollars < 0 )
            {
                /* Calculate the change owed and return it */
                printf("\nThank you. Here is your %s, "
                               "and your change of $%d.%02d.\n",
                       purchaseItem->data->name, abs(remainingDollars) - 1,
                       100 - remainingCents );

                return TRUE;
            }
            else
                /* Re-loop for remaining value needed */
                continue;
        }
        else
        {
            printf("Error: $%d.%02d is not a valid denomination of money.\n",
                   dollarExtract, centExtract);
            continue;
        }
    }
}
