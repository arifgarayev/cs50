#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    char  *s = get_string("i: ");
    char *t = get_string("j: ");
    char **p = &s;


    printf("%p\n%p\n%p\n", s, t, p);


}