#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>


int main(void)
{
    string s = get_string("Before: ");
    printf("After: ");


    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (islower(s[i])) // (s[i] >= 'a' && s[i] <= 'z')
        {
            //printf("%c", s[i] - 32);

            printf("%c", toupper(s[i]));
        }
        else
        {
            printf("%c", s[i]);
        }
    }

    printf("\n");


}