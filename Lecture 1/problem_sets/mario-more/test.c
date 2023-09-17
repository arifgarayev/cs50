#include <stdio.h>
#include <cs50.h>

int checksum(long number);

int main(void){

    printf("%i\n", checksum(2221000000000009));

    if (checksum(2221000000000009))
    {
        printf("TRUE\n");
    }
}



int checksum(long number)
{


    int first = number % 10, second = (number / 10) % 10, third = (number / 100) % 10, fourth = (number / 1000) % 10, fifth = (number / 10000) % 10, sixth = (number / 100000) % 10, seventh = (number / 1000000) % 10, eighth = (number / 10000000) % 10, ninth = (number / 100000000) % 10, tenth = (number / 1000000000) % 10, eleventh = (number / 10000000000) % 10, twelveth = (number / 100000000000) % 10, thirteenth = (number / 1000000000000) % 10, fourteenth = (number / 10000000000000) % 10, fifteenth = (number / 100000000000000) % 10, sixteenth = (number / 1000000000000000) % 10;

        // as soon as there shouldn't be more than 9 and 9 * 2 = 18 maximum number is 18, so we can take every numbers modulo 10.
    int sum = (((second * 2) % 10) + first + (second * 2) / 10) + third + (((fourth * 2) % 10) + fifth + (fourth * 2) / 10) + seventh + (((sixth * 2) % 10) + ninth + (sixth * 2) / 10) + eleventh + (((eighth * 2) % 10) + thirteenth + (eighth * 2) / 10) + fifteenth + (((tenth * 2) % 10) + (tenth * 2) / 10) + (((twelveth * 2) % 10) + (twelveth * 2) / 10) + (((fourteenth * 2) % 10) + (fourteenth * 2) / 10) + (((sixteenth * 2) % 10) + (sixteenth * 2) / 10);

    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}