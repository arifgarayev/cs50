#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

void compute_score(string word);


int main(void)
{
    compute_score("Salam");
}

void compute_score(string word)
{
    char word_array[strlen(word)];

    for (int i=0, n=strlen(word); i < n; i++)
    {
        word_array[i] = word[i];

        if (isupper(word_array[i]))
        {
            word_array[i] = word_array[i] + 32;
        }
    }

}
