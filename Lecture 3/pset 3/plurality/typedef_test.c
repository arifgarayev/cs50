#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct
{
    int votes;
}
candidate;


void print_winner(void);

int main(void)
{
    candidate candidates[5];

    for (int i = 0; i < 5; i++)
    {
        candidates[i].votes = random();
    }

    print_winner();

}


void print_winner(void)
{
    int biggest_index = 0;

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int k = 0; k <= i + 1; k++)
        {
            if (!(candidates[i].votes > candidates[k].votes))
            {
                biggest_index = k;
            }
        }
    }
}