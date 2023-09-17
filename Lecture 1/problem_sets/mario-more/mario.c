#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x;
    char block = '#';
    do
    {
        x = get_int("Height: ");

        // check whether meet requirements to do a task only once
        if (x > 0 && x <= 8)
        {

            for (int i = 1; i <= x; i++)
            {
                for (int j = 0; j <= x - i; j++)
                {
                    if (j == x - i)
                    {
                        printf("%c", block);

                        for (int l = 1; l < i; l++)
                        {
                            printf("%c", block);

                        }
                    }
                    else
                    {
                        printf(" ");
                    }
                }

                for (int j = 0; j <= i; j++)
                {
                    if (j == i)
                    {
                        printf("  ");

                        for (int l = 0; l < i; l++)
                        {
                            printf("%c", block);

                        }
                        printf("\n");
                    }


                }


                // for (int l=0; l <= 1; l++){
                //     printf(" ");
                // }
                // printf("%c\n", block);
            }

        }


    }
    // do until x doesn't meet the requirements
    while (x <= 0 || x > 8);
}

