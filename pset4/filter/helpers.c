#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float averagePix = ((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = nearbyint(averagePix);
            image[i][j].rgbtGreen = nearbyint(averagePix);
            image[i][j].rgbtRed = nearbyint(averagePix);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int newRED = 0;
    int newGREEN = 0;
    int newBLUE = 0;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue) > 255)
                newRED = 255;
                
                
            if ((0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue) <= 255)
                newRED = nearbyint(0.393 * (float)image[i][j].rgbtRed + 0.769 * (float)image[i][j].rgbtGreen + 0.189 * (float)image[i][j].rgbtBlue);
                
                
            if ((0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue) > 255)
                newGREEN = 255;
                
                
            if ((0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue) <= 255)
                newGREEN = nearbyint(0.349 * (float)image[i][j].rgbtRed + 0.686 * (float)image[i][j].rgbtGreen + 0.168 * (float)image[i][j].rgbtBlue);
                
                
            if ((0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue) > 255)
                newBLUE = 255;
                
                
            if ((0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue) <= 255)
                newBLUE = nearbyint(0.272 * (float)image[i][j].rgbtRed + 0.534 * (float)image[i][j].rgbtGreen + 0.131 * (float)image[i][j].rgbtBlue);
        
            image[i][j].rgbtRed = newRED;
            image[i][j].rgbtGreen = newGREEN;
            image[i][j].rgbtBlue = newBLUE;
            
        }
        
        
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < ceil(width/2); j++)
        {
            int bullshit = width - j - 1;
            BYTE tempPixRED = image[i][bullshit].rgbtRed;
            image[i][bullshit].rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = tempPixRED;
            
            BYTE tempPixGREEN = image[i][bullshit].rgbtGreen;
            image[i][bullshit].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = tempPixGREEN;
            
            BYTE tempPixBLUE = image[i][bullshit].rgbtBlue;
            image[i][bullshit].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = tempPixBLUE;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempimage[height][width];
    int newBLUE = 0;
    int newGREEN = 0;
    int newRED = 0;
    
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            tempimage[i][j] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //bottom edge (excluding corners)
            if (i == 0 && j != 0 && j != width-1)
            {
                image[i][j].rgbtBlue = (int)((((float)tempimage[i][j].rgbtBlue + (float)tempimage[i+1][j].rgbtBlue + (float)tempimage[i+1][j-1].rgbtBlue + (float)tempimage[i+1][j+1].rgbtBlue + (float)tempimage[i][j-1].rgbtBlue + (float)tempimage[i][j+1].rgbtBlue) /6) + 0.5); 
                image[i][j].rgbtRed = (int)((((float)tempimage[i][j].rgbtRed + (float)tempimage[i+1][j].rgbtRed + (float)tempimage[i+1][j-1].rgbtRed + (float)tempimage[i+1][j+1].rgbtRed + (float)tempimage[i][j-1].rgbtRed + (float)tempimage[i][j+1].rgbtRed) /6) + 0.5);
                image[i][j].rgbtGreen = (int)((((float)tempimage[i][j].rgbtGreen + (float)tempimage[i+1][j].rgbtGreen + (float)tempimage[i+1][j-1].rgbtGreen + (float)tempimage[i+1][j+1].rgbtGreen + (float)tempimage[i][j-1].rgbtGreen + (float)tempimage[i][j+1].rgbtGreen) /6) + 0.5);
                continue;
            }
            //top edge (excluding corners)
            if (i == height-1 && j != 0 && j != width-1)
            {
                image[i][j].rgbtBlue = (int)((((float)tempimage[i][j].rgbtBlue + (float)tempimage[i-1][j].rgbtBlue + (float)tempimage[i-1][j-1].rgbtBlue + (float)tempimage[i-1][j+1].rgbtBlue + (float)tempimage[i][j-1].rgbtBlue + (float)tempimage[i][j+1].rgbtBlue) /6) + 0.5); 
                image[i][j].rgbtRed = (int)((((float)tempimage[i][j].rgbtRed + (float)tempimage[i-1][j].rgbtRed + (float)tempimage[i-1][j-1].rgbtRed + (float)tempimage[i-1][j+1].rgbtRed + (float)tempimage[i][j-1].rgbtRed + (float)tempimage[i][j+1].rgbtRed) /6) + 0.5);
                image[i][j].rgbtGreen = (int)((((float)tempimage[i][j].rgbtGreen + (float)tempimage[i-1][j].rgbtGreen + (float)tempimage[i-1][j-1].rgbtGreen + (float)tempimage[i-1][j+1].rgbtGreen + (float)tempimage[i][j-1].rgbtGreen + (float)tempimage[i][j+1].rgbtGreen) /6) + 0.5);
                continue;
            }
            //left edge (excluding corners)
            if (j == 0 && i != 0 && i != height-1)
            {
                image[i][j].rgbtBlue = (int)((((float)tempimage[i][j].rgbtBlue + (float)tempimage[i+1][j].rgbtBlue + (float)tempimage[i-1][j].rgbtBlue + (float)tempimage[i+1][j+1].rgbtBlue + (float)tempimage[i-1][j+1].rgbtBlue + (float)tempimage[i][j+1].rgbtBlue) /6) + 0.5); 
                image[i][j].rgbtRed = (int)((((float)tempimage[i][j].rgbtRed + (float)tempimage[i+1][j].rgbtRed + (float)tempimage[i-1][j].rgbtRed + (float)tempimage[i+1][j+1].rgbtRed + (float)tempimage[i-1][j+1].rgbtRed + (float)tempimage[i][j+1].rgbtRed) /6) + 0.5);
                image[i][j].rgbtGreen = (int)((((float)tempimage[i][j].rgbtGreen + (float)tempimage[i+1][j].rgbtGreen + (float)tempimage[i-1][j].rgbtGreen + (float)tempimage[i+1][j+1].rgbtGreen + (float)tempimage[i-1][j+1].rgbtGreen + (float)tempimage[i][j+1].rgbtGreen) /6) + 0.5);
                continue;
            }
            //right edge (excluding corners)
            if (j == width-1 && i != 0 && i != height-1)
            {
                image[i][j].rgbtBlue = (int)((((float)tempimage[i][j].rgbtBlue + (float)tempimage[i+1][j].rgbtBlue + (float)tempimage[i-1][j].rgbtBlue + (float)tempimage[i+1][j-1].rgbtBlue + (float)tempimage[i-1][j-1].rgbtBlue + (float)tempimage[i][j-1].rgbtBlue) /6) + 0.5); 
                image[i][j].rgbtRed = (int)((((float)tempimage[i][j].rgbtRed + (float)tempimage[i+1][j].rgbtRed + (float)tempimage[i-1][j].rgbtRed + (float)tempimage[i+1][j-1].rgbtRed + (float)tempimage[i-1][j-1].rgbtRed + (float)tempimage[i][j-1].rgbtRed) /6) + 0.5);
                image[i][j].rgbtGreen = (int)((((float)tempimage[i][j].rgbtGreen + (float)tempimage[i+1][j].rgbtGreen + (float)tempimage[i-1][j].rgbtGreen + (float)tempimage[i+1][j-1].rgbtGreen + (float)tempimage[i-1][j-1].rgbtGreen + (float)tempimage[i][j-1].rgbtGreen) /6) + 0.5);
                continue;
            }
            //corner
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtBlue = (int)((((float)tempimage[i][j].rgbtBlue + (float)tempimage[i+1][j].rgbtBlue + (float)tempimage[i+1][j+1].rgbtBlue + (float)tempimage[i][j+1].rgbtBlue) /4) + 0.5); 
                image[i][j].rgbtRed = (int)((((float)tempimage[i][j].rgbtRed + (float)tempimage[i+1][j].rgbtRed + (float)tempimage[i+1][j+1].rgbtRed + (float)tempimage[i][j+1].rgbtRed) /4) + 0.5);
                image[i][j].rgbtGreen = (int)((((float)tempimage[i][j].rgbtGreen + (float)tempimage[i+1][j].rgbtGreen + (float)tempimage[i+1][j+1].rgbtGreen + (float)tempimage[i][j+1].rgbtGreen) /4) + 0.5);
                continue;
            }
            //corner
            if (i == 0 && j == width-1)
            {
                image[i][j].rgbtBlue = (int)((((float)tempimage[i][j].rgbtBlue + (float)tempimage[i+1][j].rgbtBlue + (float)tempimage[i+1][j-1].rgbtBlue + (float)tempimage[i][j-1].rgbtBlue) /4) + 0.5); 
                image[i][j].rgbtRed= (int)((((float)tempimage[i][j].rgbtRed + (float)tempimage[i+1][j].rgbtRed + (float)tempimage[i+1][j-1].rgbtRed + (float)tempimage[i][j-1].rgbtRed) /4) + 0.5);
                image[i][j].rgbtGreen = (int)((((float)tempimage[i][j].rgbtGreen + (float)tempimage[i+1][j].rgbtGreen + (float)tempimage[i+1][j-1].rgbtGreen + (float)tempimage[i][j-1].rgbtGreen) /4) + 0.5);
                continue;
            }
            //corner
            if (i == height-1 && j == width-1)
            {
                image[i][j].rgbtBlue = (int)((((float)tempimage[i][j].rgbtBlue + (float)tempimage[i-1][j].rgbtBlue + (float)tempimage[i-1][j-1].rgbtBlue + (float)tempimage[i][j-1].rgbtBlue) /4) + 0.5); 
                image[i][j].rgbtRed = (int)((((float)tempimage[i][j].rgbtRed + (float)tempimage[i-1][j].rgbtRed + (float)tempimage[i-1][j-1].rgbtRed + (float)tempimage[i][j-1].rgbtRed) /4)+ 0.5);
                image[i][j].rgbtGreen = (int)((((float)tempimage[i][j].rgbtGreen + (float)tempimage[i-1][j].rgbtGreen + (float)tempimage[i-1][j-1].rgbtGreen + (float)tempimage[i][j-1].rgbtGreen) /4) + 0.5);
                continue;
            }
            //corner
            if (i == height-1 && j == 0)
            {
                image[i][j].rgbtBlue = (int)((((float)tempimage[i][j].rgbtBlue + (float)tempimage[i-1][j].rgbtBlue + (float)tempimage[i-1][j+1].rgbtBlue + (float)tempimage[i][j+1].rgbtBlue) /4) + 0.5); 
                image[i][j].rgbtRed= (int)((((float)tempimage[i][j].rgbtRed + (float)tempimage[i-1][j].rgbtRed + (float)tempimage[i-1][j+1].rgbtRed + (float)tempimage[i][j+1].rgbtRed) /4) + 0.5);
                image[i][j].rgbtGreen = (int)((((float)tempimage[i][j].rgbtGreen + (float)tempimage[i-1][j].rgbtGreen + (float)tempimage[i-1][j+1].rgbtGreen + (float)tempimage[i][j+1].rgbtGreen) /4) + 0.5);
                continue;
            }
            //middle
            if (i != 0 && i != height-1 && j != 0 && j != width-1)
            {
                image[i][j].rgbtBlue = floor((((float)tempimage[i][j].rgbtBlue + (float)tempimage[i-1][j].rgbtBlue + (float)tempimage[i-1][j-1].rgbtBlue + (float)tempimage[i-1][j+1].rgbtBlue + (float)tempimage[i+1][j].rgbtBlue + (float)tempimage[i+1][j-1].rgbtBlue + (float)tempimage[i+1][j+1].rgbtBlue + (float)tempimage[i][j-1].rgbtBlue + (float)tempimage[i][j+1].rgbtBlue) / 9.0) + 0.5); 
                image[i][j].rgbtRed = floor((((float)tempimage[i][j].rgbtRed + (float)tempimage[i-1][j].rgbtRed + (float)tempimage[i-1][j-1].rgbtRed + (float)tempimage[i-1][j+1].rgbtRed + (float)tempimage[i+1][j].rgbtRed + (float)tempimage[i+1][j-1].rgbtRed + (float)tempimage[i+1][j+1].rgbtRed + (float)tempimage[i][j-1].rgbtRed + (float)tempimage[i][j+1].rgbtRed) / 9.0) + 0.5);
                image[i][j].rgbtGreen = floor((((float)tempimage[i][j].rgbtGreen + (float)tempimage[i-1][j].rgbtGreen + (float)tempimage[i-1][j-1].rgbtGreen + (float)tempimage[i-1][j+1].rgbtGreen + (float)tempimage[i+1][j].rgbtGreen + (float)tempimage[i+1][j-1].rgbtGreen + (float)tempimage[i+1][j+1].rgbtGreen + (float)tempimage[i][j-1].rgbtGreen + (float)tempimage[i][j+1].rgbtGreen) / 9.0) + 0.5);
            }
        }
    }
    return;
}
