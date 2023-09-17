#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = malloc(10 * sizeof(char));

    printf("s: ");

    scanf("%s", s);

    printf("s: %s\n", s);

}