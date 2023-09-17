#include <stdio.h>
#include <cs50.h>

int triangle(int x, int y, int z);

int main(void)
{
    int x = get_int("Type X: "), y = get_int("Type Y: "), z = get_int("Type Z: ");

    if (triangle(x, y, z))
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }
}

int triangle(int x, int y, int z)
{
    while (x > 0 && y > 0 && z > 0)
    {
        if (x + y > z && x + z > y && y + z > x)
        {
            return 1;
        }
        return 0;
    }
    return 0;

}