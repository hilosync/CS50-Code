#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2) 
    {
        printf("Usage: ./ceasar key\n");
        exit(1);
    }

    for (int i = 0; i>=0; i++)
    {
        if (argv[1][i] >= 47 && argv[1][i] <= 57)
        {
            continue;
        }
        else if (argv[1][i] == '\0')
        {
            break;
        }
        else
        {
           printf("Usage: ./ceasar key\n");
           exit(1);
        }
    }
    printf("%s\n", argv[1]);
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    
    for (int i = 0; i>=0;i++)
    {
        if(plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            plaintext[i] = (((plaintext[i] - 97) + key) % 26) + 97;
        }
        else if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            plaintext[i] = (((plaintext[i] - 65) + key) % 26) + 65;
        }
        else if (plaintext[i] == '\0')
        {
            break;
        }
        else
        {
            continue;
        }
    }
    
   printf("ciphertext: %s\n", plaintext);
    
    
    
    
    
}
