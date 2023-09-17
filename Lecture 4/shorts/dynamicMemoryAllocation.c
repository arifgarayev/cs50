#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    // int *x = malloc(sizeof(int));

    // *x = 5;

    // printf("%i\n", *x);

    float* heapArray = malloc(5 * sizeof(float));

    heapArray[0] = 5.4;

    printf("%f\n", heapArray[0]);
}