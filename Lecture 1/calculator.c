#include <stdio.h>
#include <cs50.h>

int main(void){

    int x = get_int("x: ");
    int y = get_int("y: ");

    // Divide x by y

    float z = (float) x / (float) y;


    printf("%.2f\n", z);

}