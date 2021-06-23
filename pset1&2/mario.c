#include <stdio.h>
#include <cs50.h>





int main(void)
{
    int n;
    do
    {
        n = get_int("height between 1 and 8: ");
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        for (int x = (n-i); x > 1; x--)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
         for (int z = 0; z <= i; z++)
        {
            printf("#");
        }
        printf("\n");
    }







}