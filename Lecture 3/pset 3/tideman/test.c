#include <stdio.h>
#include <cs50.h>
#include <string.h>


#define MAX 9

int main(int argc, string argv[])
{

    typedef struct
    {
        int winner;
        int loser;
    }
    pair;

    // Array of candidates
    string candidates[MAX];
    pair pairs[MAX * (MAX - 1) / 2];

    pairs[0].winner = 1;
    pairs[0].loser = 23;

    printf("%i\n", pairs[0].loser);

}