#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void split_string(string str_key);
int get_index(char letter);

char key[26];

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else if (tolower(argv[1][i]) == tolower(argv[1][i + 1]))
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    split_string(argv[1]);

    string plaintext = get_string("plaintext: ");

    char converted[strlen(plaintext)];
    int counter = 0;

    while (plaintext[counter] != '\0')
    {
        if (isalpha(plaintext[counter]))
        {
            if (isupper(plaintext[counter]))
            {
                // translate to uppercase
                converted[counter] = toupper(key[get_index(plaintext[counter])]);
            }
            else
            {
                //translate to lowercase
                converted[counter] = tolower(key[get_index(plaintext[counter])]);
            }
        }
        //if not alphabetic char or any whitespace
        else
        {
            converted[counter] = plaintext[counter];
        }

        counter++;

    }

    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", converted[i]);
    }
    printf("\n");

    return 0;


}


void split_string(string str_key)
{
    for (int i = 0; i < 26; i++)
    {
        // if (isalnum(str_key[i]))
        // {
        key[i] = str_key[i];
        // }

    }
}


int get_index(char letter)
{
    if (tolower(letter) - 97 < 0 || tolower(letter) - 97 > 25)
    {
        return -1;
    }
    else
    {
        return tolower(letter) - 97;
    }
}

// int array_of_indicies(string plain)
// {
//     int indices[strlen(plain)];

//     for (int i = 0, n = strlen(plain); i < n; i++)
//     {
//         if (isalpha(plain[i]))
//         {
//             indices[i] = get_index(plain[i]);
//         }
//         else
//         {
//             indices[i] = plain[i];
//         }

//     }

//     return indices;
// }