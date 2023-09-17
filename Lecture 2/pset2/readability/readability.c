#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string sentence);
int count_words(string sentence);
int count_sentences(string sentences);

int main(void)
{
    string sentence = get_string("Text: ");

    int letters = count_letters(sentence), words = count_words(sentence), sentences = count_sentences(sentence);

    // printf("%i letters\n", letters);

    // printf("%i words\n", words);

    // printf("%i sentences\n", sentences);

    double index = ((0.0588 * (((float) letters / words) * 100)) - (0.296 * (((float) sentences / words) * 100))) - 15.8;

    // printf("%f\n", index);

    int result = round(index);

    if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (result >= 16)
    {
        //loool what am I doind ?
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", result);
    }


}

// more comments)
int count_letters(string sentence)
{
    int counter = 0;
    for (int i = 0, n = strlen(sentence); i < n; i++)
    {
        //emioglu
        if ((sentence[i] >= 65 && sentence[i] <= 90) || (sentence[i] >= 97 && sentence[i] <= 122))
        {
            counter++;
        }
    }

    return counter;
}

// more and moreeeee
int count_words(string sentence)
{
    int counter;

    if (sentence[0] == 32)
    {
        counter = 0;
    }
    else
    {
        counter = 1;
    }
    //simple for loop)
    for (int i = 0, n = strlen(sentence); i <= n; i++)
    {

        if (sentence[i] == 32 && isalpha(sentence[i + 1]))
        {
            counter++;
        }

    }

    return counter;

}

//mystyle is the best)
int count_sentences(string sentences)
{
    int counter = 0, i = 0;
    while (sentences[i] != '\0')
    {
        //comment here too
        if (sentences[i] == 33 || sentences[i] == 46 || sentences[i] == 63)
        {
            counter++;
        }

        i++;
    }
//another comment
    return counter;
}