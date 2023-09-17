// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <math.h>



#include "dictionary.h"
void print_str(const char *myString);
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

int wordCounter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    int index = hash(word);
    node *myNode = table[index];


    while (myNode != NULL)
    {
        if (strcasecmp(word, myNode->word) == 0)
        {
            return true;
        }
        else
        {
            myNode = myNode->next;
        }
    }

    return false;









    // for (node *j = myNode; j != NULL; j = j->next)
    // {
    //     if (strcasecmp(word, j->word) == 0)
    //     {
    //         // printf("Word: ");
    //         // print_str(word);
    //         // printf("\n");
    //         // printf("j->word: ");
    //         // print_str(j->word);
    //         return true;
    //     }
    // }

    // return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{


    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ tolower(word[i]);
    }
    return hash % N;



    // TODO: Improve this hash function
    // int base = 13;
    // int hash = 0;


    // for (int index = 0; word[index] != '\0'; index++)
    // {
    //     hash += tolower(word[index]) * pow(base, (strlen(word) - index - 1));
    // }

    // if (hash % (strlen(word) * 2) >= N)
    // {

    //     if (hash % strlen(word) >= N)
    //     {
    //         return hash % strlen(word) / 2;
    //     }

    //     return hash % strlen(word);
    // }


    // return hash % (strlen(word) * 2);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *fileO = fopen(dictionary, "r");

    if (fileO == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(fileO, "%s", word) != EOF)
    {
        // malloc new node
        node *newNode = malloc(sizeof(node));

        if (newNode == NULL)
        {
            unload();
            return false;
        }

        // copy string from dictionary into node
        strcpy(newNode->word, word);
        newNode->next = NULL; // set next pointer to null



        unsigned int hashIndex = hash(word);

        // printf("Hash code is ---> %i\nWord is ---> ", hashIndex);
        // print_str(word);


        // printf("Hash index is: %i\n", hashIndex);
        if (table[hashIndex] == NULL)
        {
            // printf("First Link - Hash Code is ---> %i\n", hashIndex);
            // printf("\n");
            table[hashIndex] = newNode;
        }
        else
        {
            newNode->next = table[hashIndex];
            table[hashIndex] = newNode;
        }


        wordCounter++;
    }
    fclose(fileO);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // DONE
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *tmp;
        node *cursor = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;

            cursor = cursor->next;

            free(tmp);
        }

        //free(tmp);
        //free(cursor);

    }

    return true;
}


void print_str(const char *myString)
{
    while (*myString)
    {
        printf("%c", *myString);
        myString++;
    }
    printf("\n");
}