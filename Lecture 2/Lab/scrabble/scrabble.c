#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
int get_index(char letter);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie!\n");
    }
    // TODO: Print the winner
}

int compute_score(string word)
{
    // make all lowercase and split string into chars of array
    char word_array[strlen(word)];
    int total = 0;


    for (int i = 0, n = strlen(word); i < n; i++)
    {
        word_array[i] = word[i];

        if (isupper(word_array[i]))
        {
            word_array[i] = word_array[i] + 32;
        }
        // end of lowercase

        //start computing points
        // I use ASCII chart table to respresent every chars index for points by ASCII number that represents
        // i.e char "a" in ASCII - 97, but index for its point in the PONTS[] array - 0
        // so char - 97 = index in POINTS[] array
        int index_of_char = get_index(word_array[i]);


        if (index_of_char != -1)
        {
            total += POINTS[index_of_char];
        }

    }

    return total;

}

//get index of a POINT by ASCII
int get_index(char letter)
{
    if (letter - 97 < 0 || letter - 97 > 25)
    {
        return -1;
    }
    else
    {
        return letter - 97;
    }
}
