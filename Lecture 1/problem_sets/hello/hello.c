#include <stdio.h>
#include <cs50.h>

int main(void)
{

    // Get input data from user
    string name = get_string("What is your name? ");

    // Display hello)
    printf("hello, %s\n", name);
}