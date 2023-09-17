#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{

    int prefs[9][9];

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            prefs[i][j] = rand();

            printf("%i ", prefs[i][j]);
        }
        printf("\n\n\n\n\n");
    }


}


