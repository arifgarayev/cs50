#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    node *head = malloc(sizeof(node));
    if (head == NULL)
    {
        return 1;
    }



    head->number = 1;
    head->next = malloc(sizeof(node));

    head->next->number = 2;
    head->next->next = NULL;

    printf("%i\n", head->next->number);


}
