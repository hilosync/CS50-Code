#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
float sentences = 0;
float letters = 0;
float words = 1;

float S = 0.0;
float L = 0.0;

string sentence = get_string("Please input a string : \n");


for (int i = 0; 1 ; i++)
{
    if (sentence[i] == ' ')
    {
        words++;
    }
    else if (sentence[i] == '!' || sentence[i] == '.' || sentence[i] == '?')
    {
        sentences++;
    }
    else if (sentence[i] == '\0')
    {
        break;
    }
    else if((sentence[i] >= 97 && sentence[i] <= 122) || (sentence[i] >= 65 && sentence[i] <= 90))
    {
        letters++;
    }
    else
    {
        continue;
    }
}

L = ((letters/words) * 100.0000);
S = ((sentences/words) * 100.0000);


float index = (0.0588 * L) - (0.296 * S) - 15.8;

if (index < 1)
{
    printf("Before Grade 1\n");
}
else if (index >= 16)
{
    printf("Grade 16+\n");
}
else
{
    printf("Grade %.0f\n", index);
}
}

