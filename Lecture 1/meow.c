#include <cs50.h>
#include <stdio.h>

void meow(int n); // to make program know that function exists and write code in any order


int main(void){
    meow(5);
}




void meow(int n){

    for (int i = 0; i < n; i++){


        printf("Meow\n");

    }

}

