#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void pass(char *c)
{
    printf("Location in pass func: %p\n", c);
}


int main(void)
{
    char* ch = "Salam aleykum";

    printf("Location in main func: %p\n", ch);

    pass(ch);
}