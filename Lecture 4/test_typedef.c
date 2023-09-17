#include <stdio.h>

typedef struct
{
    char *name;
    char *age;
}
person;


typedef struct char *string;


int main(void)
{
    person first;

    first.name = "Arif";
    first.age = "5";
    printf("%p\n", &first.age);

}