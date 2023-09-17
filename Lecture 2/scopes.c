#include <stdio.h>
#include <cs50.h>

void triple(void);

float global = 0.5050;

int main(void)
{
    triple();
    printf("%f\n", global);
}


void triple(void)
{
    global *= 3;
}