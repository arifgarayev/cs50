#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string sentence = "Salam qaqaw? Necesen? Mence. Yaxwi! Sola.";
    int counter=0, i=0;
    while (sentence[i] != '\0')
    {
        if (sentence[i] == 33 || sentence[i] == 46 || sentence[i] == 63)
        {
            counter++;
        }

        i++;
    }

    printf("%i\n", counter);

}