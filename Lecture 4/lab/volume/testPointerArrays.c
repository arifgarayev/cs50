#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

const int HEADER_SIZE = 44;

int main(void)
{
    int *in_header = malloc(sizeof(int) * HEADER_SIZE);

    in_header[0] = 4;
    in_header[1] = 5;

    printf("%i - %i\n", *in_header, *in_header)[1]);
}