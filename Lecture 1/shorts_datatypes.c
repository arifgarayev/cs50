#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){

    int x = get_int("Input: ");

    switch(x){

        case 1:
            printf("One!\n");
            break;
        case 2:
            printf("Two\n");
            break;
        default:
            printf("Sorry\n");


    }

}