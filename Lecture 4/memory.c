#include <stdlib.h>
#include <stdio.h>

int main(void)
{

    int *x = malloc(3 * sizeof(int));


    x[1] = 72;
    x[2] = 799;
    x[3] = 74;

    printf("%p\n", x);

    free(x);

    return 0;
}