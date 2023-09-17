#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(void)
{
    int arr[11] = {3, 7, 4, 2, 0, 5, 2, 4, 8, 0, 4};
    int smallest, smallest_index;

    for (int i = 0; i < 11; i++)
    {
        smallest = arr[i], smallest_index = i;

        for (int j = i + 1; j < 11; j++)
        {
            if (smallest > arr[j])
            {
                smallest = arr[j];
                smallest_index = j;
            }
        }
        arr[smallest_index] = arr[i];
        arr[i] = smallest;

        printf("%i ", arr[i]);
    }

}