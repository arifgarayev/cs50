#include <stdio.h>
#include <cs50.h>


int main(void){

    int n;

    do{
        n = get_int("Size: ");
    }
    while (n < 1);


//         OR YOU CAN USE THIS ONE


    // while (true){
    //     n = get_int("Size: ");

    //     if (n > 0){
    //         break
    //     }
    // }


    // for each row
    for (int i=0; i < n; i++){

        //for each column
        for (int j = 0; j < n; j++){
            printf("#");
        }

        // move to. next row
        printf("\n");
    }




}