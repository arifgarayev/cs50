#include <stdio.h>
#include <math.h>
#include "helpers.h"

void copyArray(int height, int width, RGBTRIPLE original[height][width], RGBTRIPLE modified[height][width]);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            float sum = round(((float) pixel.rgbtBlue + (float) pixel.rgbtGreen + (float) pixel.rgbtRed) / 3);

            // printf("%i + %i + %i \n", pixel.rgbtBlue, pixel.rgbtGreen, pixel.rgbtRed);
            // printf("%f\n", sum);
            // printf("%i\n", (BYTE) sum);


            image[i][j].rgbtBlue = (BYTE) sum;
            image[i][j].rgbtGreen = (BYTE) sum;
            image[i][j].rgbtRed = (BYTE) sum;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        //int _i = height - i - 1;


        for (int j = 0; j < (int) width / 2; j++)
        {
            int _j = width - j - 1;

            //RGBTRIPLE left = image[i][j];
            RGBTRIPLE right = image[i][_j];
            // RGBTRIPLE tmp[i][j] = image[_i][_j];
            image[i][_j] = image[i][j];
            image[i][j] = right;

        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // printf("%i\n %i\n", height, width);

    RGBTRIPLE blurredImage[height][width];

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            int row = i, col = j;

            // printf("%i\n %i\n", row, col);

            if (row > 0 && row < height - 1)
            {

                // printf("%f\n", (float) image[row-1][col-1].rgbtBlue);
                // printf("%f\n", (float) image[row-1][col].rgbtBlue);
                // printf("%f\n", (float) image[row-1][col+1].rgbtBlue);

                if (col > 0 && col < width - 1)
                {
                    float blue = round(((float) image[row-1][col-1].rgbtBlue
                    + (float) image[row-1][col].rgbtBlue
                    + (float) image[row-1][col+1].rgbtBlue
                    + (float) image[row][col-1].rgbtBlue
                    + (float) image[row][col].rgbtBlue
                    + (float) image[row][col+1].rgbtBlue
                    + (float) image[row+1][col-1].rgbtBlue
                    + (float) image[row+1][col].rgbtBlue
                    + (float) image[row+1][col+1].rgbtBlue) / 9);

                    // if (blue == (float) image[i][j].rgbtBlue)
                    // {
                    //     printf("Nothing modified\n");
                    // }

                    float red = round(((float) image[row-1][col-1].rgbtRed
                    + (float) image[row-1][col].rgbtRed
                    + (float) image[row-1][col+1].rgbtRed
                    + (float) image[row][col-1].rgbtRed
                    + (float) image[row][col].rgbtRed
                    + (float) image[row][col+1].rgbtRed
                    + (float) image[row+1][col-1].rgbtRed
                    + (float) image[row+1][col].rgbtRed
                    + (float) image[row+1][col+1].rgbtRed) / 9);

                    float green = round(((float) image[row-1][col-1].rgbtGreen
                    + (float) image[row-1][col].rgbtGreen
                    + (float) image[row-1][col+1].rgbtGreen
                    + (float) image[row][col-1].rgbtGreen
                    + (float) image[row][col].rgbtGreen
                    + (float) image[row][col+1].rgbtGreen
                    + (float) image[row+1][col-1].rgbtGreen
                    + (float) image[row+1][col].rgbtGreen
                    + (float) image[row+1][col+1].rgbtGreen) / 9);

                    blurredImage[i][j].rgbtBlue = (BYTE) blue;
                    blurredImage[i][j].rgbtRed = (BYTE) red;
                    blurredImage[i][j].rgbtGreen = (BYTE) green;

                }

                else if (col == 0)
                {
                    float blue = round(((float) image[row-1][col].rgbtBlue
                    + (float) image[row-1][col+1].rgbtBlue
                    + (float) image[row][col].rgbtBlue
                    + (float) image[row][col+1].rgbtBlue
                    + (float) image[row+1][col].rgbtBlue
                    + (float) image[row+1][col+1].rgbtBlue) / 6);

                    // if (blue == (float) image[i][j].rgbtBlue)
                    // {
                    //     printf("Nothing modified\n");
                    // }

                    float red = round(((float) image[row-1][col].rgbtRed
                    + (float) image[row-1][col+1].rgbtRed
                    + (float) image[row][col].rgbtRed
                    + (float) image[row][col+1].rgbtRed
                    + (float) image[row+1][col].rgbtRed
                    + (float) image[row+1][col+1].rgbtRed) / 6);

                    float green = round(((float) image[row-1][col].rgbtGreen
                    + (float) image[row-1][col+1].rgbtGreen
                    + (float) image[row][col].rgbtGreen
                    + (float) image[row][col+1].rgbtGreen
                    + (float) image[row+1][col].rgbtGreen
                    + (float) image[row+1][col+1].rgbtGreen) / 6);

                    blurredImage[i][j].rgbtBlue = (BYTE) blue;
                    blurredImage[i][j].rgbtRed = (BYTE) red;
                    blurredImage[i][j].rgbtGreen = (BYTE) green;

                }
                else if (col == width - 1)
                {
                    float blue = round(((float) image[row-1][col].rgbtBlue
                    + (float) image[row-1][col-1].rgbtBlue
                    + (float) image[row][col].rgbtBlue
                    + (float) image[row][col-1].rgbtBlue
                    + (float) image[row+1][col].rgbtBlue
                    + (float) image[row+1][col-1].rgbtBlue) / 6);

                    // if (blue == (float) image[i][j].rgbtBlue)
                    // {
                    //     printf("Nothing modified\n");
                    // }

                    float red = round(((float) image[row-1][col].rgbtRed
                    + (float) image[row-1][col-1].rgbtRed
                    + (float) image[row][col].rgbtRed
                    + (float) image[row][col-1].rgbtRed
                    + (float) image[row+1][col].rgbtRed
                    + (float) image[row+1][col-1].rgbtRed) / 6);

                    float green = round(((float) image[row-1][col].rgbtGreen
                    + (float) image[row-1][col-1].rgbtGreen
                    + (float) image[row][col].rgbtGreen
                    + (float) image[row][col-1].rgbtGreen
                    + (float) image[row+1][col].rgbtGreen
                    + (float) image[row+1][col-1].rgbtGreen) / 6);

                    blurredImage[i][j].rgbtBlue = (BYTE) blue;
                    blurredImage[i][j].rgbtRed = (BYTE) red;
                    blurredImage[i][j].rgbtGreen = (BYTE) green;

                }




            }
            else if (row == 0)
            {
                if (col == 0)
                {
                    float blue = round(((float) image[row][col].rgbtBlue
                    + (float) image[row][col+1].rgbtBlue
                    + (float) image[row+1][col].rgbtBlue
                    + (float) image[row+1][col+1].rgbtBlue) / 4);

                    float red = round(((float) image[row][col].rgbtRed
                    + (float) image[row][col+1].rgbtRed
                    + (float) image[row+1][col].rgbtRed
                    + (float) image[row+1][col+1].rgbtRed) / 4);

                    float green = round(((float) image[row][col].rgbtGreen
                    + (float) image[row][col+1].rgbtGreen
                    + (float) image[row+1][col].rgbtGreen
                    + (float) image[row+1][col+1].rgbtGreen) / 4);

                    blurredImage[i][j].rgbtBlue = (BYTE) blue;
                    blurredImage[i][j].rgbtRed = (BYTE) red;
                    blurredImage[i][j].rgbtGreen = (BYTE) green;
                }
                else if (col == width - 1)
                {
                    float blue = round(((float) image[row][col-1].rgbtBlue
                    + (float) image[row][col].rgbtBlue
                    + (float) image[row+1][col-1].rgbtBlue
                    + (float) image[row+1][col].rgbtBlue) / 4);

                    float red = round(((float) image[row][col-1].rgbtRed
                    + (float) image[row][col].rgbtRed
                    + (float) image[row+1][col-1].rgbtRed
                    + (float) image[row+1][col].rgbtRed) / 4);

                    float green = round(((float) image[row][col-1].rgbtGreen
                    + (float) image[row][col].rgbtGreen
                    + (float) image[row+1][col-1].rgbtGreen
                    + (float) image[row+1][col].rgbtGreen) / 4);

                    blurredImage[i][j].rgbtBlue = (BYTE) blue;
                    blurredImage[i][j].rgbtRed = (BYTE) red;
                    blurredImage[i][j].rgbtGreen = (BYTE) green;
                }
                else
                {
                    float blue = round(((float) image[row][col-1].rgbtBlue
                    + (float)  image[row][col].rgbtBlue
                    + (float)  image[row][col+1].rgbtBlue
                    + (float)  image[row+1][col-1].rgbtBlue
                    + (float)  image[row+1][col].rgbtBlue
                    + (float)  image[row+1][col+1].rgbtBlue) / 6);

                    float red = round(((float) image[row][col-1].rgbtRed
                    + (float)  image[row][col].rgbtRed
                    + (float)  image[row][col+1].rgbtRed
                    + (float)  image[row+1][col-1].rgbtRed
                    + (float)  image[row+1][col].rgbtRed
                    + (float)  image[row+1][col+1].rgbtRed) / 6);

                    float green = round(((float) image[row][col-1].rgbtGreen
                    + (float)  image[row][col].rgbtGreen
                    + (float)  image[row][col+1].rgbtGreen
                    + (float)  image[row+1][col-1].rgbtGreen
                    + (float)  image[row+1][col].rgbtGreen
                    + (float)  image[row+1][col+1].rgbtGreen) / 6);

                    blurredImage[i][j].rgbtBlue = (BYTE) blue;
                    blurredImage[i][j].rgbtRed = (BYTE) red;
                    blurredImage[i][j].rgbtGreen = (BYTE) green;

                }



            }
            else if (row == height - 1)
            {
                if (col == 0)
                {
                    float blue = round(((float) image[row][col].rgbtBlue
                    + (float) image[row][col+1].rgbtBlue
                    + (float) image[row-1][col].rgbtBlue
                    + (float) image[row-1][col+1].rgbtBlue) / 4);

                    float red = round(((float) image[row][col].rgbtRed
                    + (float) image[row][col+1].rgbtRed
                    + (float) image[row-1][col].rgbtRed
                    + (float) image[row-1][col+1].rgbtRed) / 4);

                    float green = round(((float) image[row][col].rgbtGreen
                    + (float) image[row][col+1].rgbtGreen
                    + (float) image[row-1][col].rgbtGreen
                    + (float) image[row-1][col+1].rgbtGreen) / 4);


                    blurredImage[i][j].rgbtBlue = (BYTE) blue;
                    blurredImage[i][j].rgbtRed = (BYTE) red;
                    blurredImage[i][j].rgbtGreen = (BYTE) green;
                }
                else if (col == width - 1)
                {
                    float blue = round(((float) image[row][col-1].rgbtBlue
                    + (float) image[row][col].rgbtBlue
                    + (float) image[row-1][col-1].rgbtBlue
                    + (float) image[row-1][col].rgbtBlue) / 4);

                    float red = round(((float) image[row][col-1].rgbtRed
                    + (float) image[row][col].rgbtRed
                    + (float) image[row-1][col-1].rgbtRed
                    + (float) image[row-1][col].rgbtRed) / 4);

                    float green = round(((float) image[row][col-1].rgbtGreen
                    + (float) image[row][col].rgbtGreen
                    + (float) image[row-1][col-1].rgbtGreen
                    + (float) image[row-1][col].rgbtGreen) / 4);

                    blurredImage[i][j].rgbtBlue = (BYTE) blue;
                    blurredImage[i][j].rgbtRed = (BYTE) red;
                    blurredImage[i][j].rgbtGreen = (BYTE) green;
                }
                else
                {
                    float blue = round(((float) image[row][col-1].rgbtBlue
                    + (float) image[row][col].rgbtBlue
                    + (float) image[row][col+1].rgbtBlue
                    + (float) image[row-1][col-1].rgbtBlue
                    + (float) image[row-1][col].rgbtBlue
                    + (float) image[row-1][col+1].rgbtBlue) / 6);

                    float red = round(((float) image[row][col-1].rgbtRed
                    + (float) image[row][col].rgbtRed
                    + (float) image[row][col+1].rgbtRed
                    + (float) image[row-1][col-1].rgbtRed
                    + (float) image[row-1][col].rgbtRed
                    + (float) image[row-1][col+1].rgbtRed) / 6);

                    float green = round(((float) image[row][col-1].rgbtGreen
                    + (float) image[row][col].rgbtGreen
                    + (float) image[row][col+1].rgbtGreen
                    + (float) image[row-1][col-1].rgbtGreen
                    + (float) image[row-1][col].rgbtGreen
                    + (float) image[row-1][col+1].rgbtGreen) / 6);

                    blurredImage[i][j].rgbtBlue = (BYTE) blue;
                    blurredImage[i][j].rgbtRed = (BYTE) red;
                    blurredImage[i][j].rgbtGreen = (BYTE) green;

                }

            }

        }


    }

    // copy array
    copyArray(height, width, image, blurredImage);

    // for (int i = 0; i < height; i++)
    // {

    //     for (int j = 0; j < width; j++)
    //     {
    //         image[i][j] = blurredImage[i][j];
    //     }

    // }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE edgesImage[height][width];

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            int row = i, col = j;
            if (row > 0 && row < height - 1
            && col > 0 && col < width - 1)
            {


                float blueGx = (((float) image[row-1][col-1].rgbtBlue * -1)
                + ((float) image[row-1][col+1].rgbtBlue * 1)
                + ((float) image[row][col-1].rgbtBlue * -2)
                + ((float) image[row][col+1].rgbtBlue * 2)
                + ((float) image[row+1][col-1].rgbtBlue * -1)
                + ((float) image[row+1][col+1].rgbtBlue * 1)
                );

                float blueGy = (((float) image[row-1][col-1].rgbtBlue * -1)
                + ((float) image[row-1][col].rgbtBlue * -2)
                + ((float) image[row-1][col+1].rgbtBlue * -1)
                + ((float) image[row+1][col-1].rgbtBlue * 1)
                + ((float) image[row+1][col].rgbtBlue * 2)
                + ((float) image[row+1][col+1].rgbtBlue * 1)
                );

                float redGx = (((float) image[row-1][col-1].rgbtRed * -1)
                + ((float) image[row-1][col+1].rgbtRed * 1)
                + ((float) image[row][col-1].rgbtRed * -2)
                + ((float) image[row][col+1].rgbtRed * 2)
                + ((float) image[row+1][col-1].rgbtRed * -1)
                + ((float) image[row+1][col+1].rgbtRed * 1)
                );

                float redGy = (((float) image[row-1][col-1].rgbtRed * -1)
                + ((float) image[row-1][col].rgbtRed * -2)
                + ((float) image[row-1][col+1].rgbtRed * -1)
                + ((float) image[row+1][col-1].rgbtRed * 1)
                + ((float) image[row+1][col].rgbtRed * 2)
                + ((float) image[row+1][col+1].rgbtRed * 1)
                );

                float greenGx = (((float) image[row-1][col-1].rgbtGreen * -1)
                + ((float) image[row-1][col+1].rgbtGreen * 1)
                + ((float) image[row][col-1].rgbtGreen * -2)
                + ((float) image[row][col+1].rgbtGreen * 2)
                + ((float) image[row+1][col-1].rgbtGreen * -1)
                + ((float) image[row+1][col+1].rgbtGreen * 1)
                );

                float greenGy = (((float) image[row-1][col-1].rgbtGreen * -1)
                + ((float) image[row-1][col].rgbtGreen * -2)
                + ((float) image[row-1][col+1].rgbtGreen * -1)
                + ((float) image[row+1][col-1].rgbtGreen * 1)
                + ((float) image[row+1][col].rgbtGreen * 2)
                + ((float) image[row+1][col+1].rgbtGreen * 1)
                );

                float colors[3] = {round(sqrt(pow(blueGx, 2) + pow(blueGy, 2))),
                round(sqrt(pow(redGx, 2) + pow(redGy, 2))),
                round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)))};


                for (int l = 0; l < 3; l++)
                {
                    if (colors[l] > 255)
                    {
                       colors[l] = 255;
                    }
                    else if (colors[l] < 0)
                    {
                        colors[l] = 0;
                    }
                }
                edgesImage[i][j].rgbtBlue = (BYTE) colors[0];
                edgesImage[i][j].rgbtRed = (BYTE) colors[1];
                edgesImage[i][j].rgbtGreen = (BYTE) colors[2];

            }
            else
            {
                if (row == 0)
                {
                    if (col == 0) // top left corner
                    {

                        float blueGx = (((float) image[row][col+1].rgbtBlue * 2)
                        + ((float) image[row+1][col+1].rgbtBlue * 1)
                        );

                        float blueGy = (((float) image[row+1][col].rgbtBlue * 2)
                        + ((float) image[row+1][col+1].rgbtBlue * 1)
                        );

                        float redGx = (((float) image[row][col+1].rgbtRed * 2)
                        + ((float) image[row+1][col+1].rgbtRed * 1)
                        );

                        float redGy = (((float) image[row+1][col].rgbtRed * 2)
                        + ((float) image[row+1][col+1].rgbtRed * 1)
                        );


                        float greenGx = (((float) image[row][col+1].rgbtGreen * 2)
                        + ((float) image[row+1][col+1].rgbtGreen * 1)
                        );

                        float greenGy = (((float) image[row+1][col].rgbtGreen * 2)
                        + ((float) image[row+1][col+1].rgbtGreen * 1)
                        );


                        float colors[3] = {round(sqrt(pow(blueGx, 2) + pow(blueGy, 2))),
                        round(sqrt(pow(redGx, 2) + pow(redGy, 2))),
                        round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)))};


                        for (int l = 0; l < 3; l++)
                        {
                            if (colors[l] > 255)
                            {
                            colors[l] = 255;
                            }
                            else if (colors[l] < 0)
                            {
                                colors[l] = 0;
                            }
                        }
                        edgesImage[i][j].rgbtBlue = (BYTE) colors[0];
                        edgesImage[i][j].rgbtRed = (BYTE) colors[1];
                        edgesImage[i][j].rgbtGreen = (BYTE) colors[2];

                    }
                    else if (col == width - 1)
                    {

                        float blueGx = (((float) image[row][col-1].rgbtBlue * -2)
                        + ((float) image[row+1][col-1].rgbtBlue * -1)
                        );

                        float blueGy = (((float) image[row+1][col].rgbtBlue * 2)
                        + ((float) image[row+1][col-1].rgbtBlue * 1)
                        );

                        float redGx = (((float) image[row][col-1].rgbtRed * -2)
                        + ((float) image[row+1][col-1].rgbtRed * -1)
                        );

                        float redGy = (((float) image[row+1][col].rgbtRed * 2)
                        + ((float) image[row+1][col-1].rgbtRed * 1)
                        );


                        float greenGx = (((float) image[row][col-1].rgbtGreen * -2)
                        + ((float) image[row+1][col-1].rgbtGreen * -1)
                        );

                        float greenGy = (((float) image[row+1][col].rgbtGreen * 2)
                        + ((float) image[row+1][col-1].rgbtGreen * 1)
                        );


                        float colors[3] = {round(sqrt(pow(blueGx, 2) + pow(blueGy, 2))),
                        round(sqrt(pow(redGx, 2) + pow(redGy, 2))),
                        round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)))};


                        for (int l = 0; l < 3; l++)
                        {
                            if (colors[l] > 255)
                            {
                            colors[l] = 255;
                            }
                            else if (colors[l] < 0)
                            {
                                colors[l] = 0;
                            }
                        }
                        edgesImage[i][j].rgbtBlue = (BYTE) colors[0];
                        edgesImage[i][j].rgbtRed = (BYTE) colors[1];
                        edgesImage[i][j].rgbtGreen = (BYTE) colors[2];

                    }
                    else
                    {
                        float blueGx = (((float) image[row][col-1].rgbtBlue * -2)
                        + ((float) image[row][col+1].rgbtBlue * 2)
                        + ((float) image[row+1][col-1].rgbtBlue * -1)
                        + ((float) image[row+1][col+1].rgbtBlue * 1)
                        );

                        float blueGy = (((float) image[row+1][col-1].rgbtBlue * 1)
                        + ((float) image[row+1][col].rgbtBlue * 2)
                        + ((float) image[row+1][col+1].rgbtBlue * 1)
                        );

                        float redGx = (((float) image[row][col-1].rgbtRed * -2)
                        + ((float) image[row][col+1].rgbtRed * 2)
                        + ((float) image[row+1][col-1].rgbtRed * -1)
                        + ((float) image[row+1][col+1].rgbtRed * 1)
                        );


                        float redGy = (((float) image[row+1][col-1].rgbtRed * 1)
                        + ((float) image[row+1][col].rgbtRed * 2)
                        + ((float) image[row+1][col+1].rgbtRed * 1)
                        );


                        float greenGx = (((float) image[row][col-1].rgbtGreen * -2)
                        + ((float) image[row][col+1].rgbtGreen * 2)
                        + ((float) image[row+1][col-1].rgbtGreen * -1)
                        + ((float) image[row+1][col+1].rgbtGreen * 1)
                        );

                        float greenGy = (((float) image[row+1][col-1].rgbtGreen * 1)
                        + ((float) image[row+1][col].rgbtGreen * 2)
                        + ((float) image[row+1][col+1].rgbtGreen * 1)
                        );

                        float colors[3] = {round(sqrt(pow(blueGx, 2) + pow(blueGy, 2))),
                        round(sqrt(pow(redGx, 2) + pow(redGy, 2))),
                        round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)))};


                        for (int l = 0; l < 3; l++)
                        {
                            if (colors[l] > 255)
                            {
                            colors[l] = 255;
                            }
                            else if (colors[l] < 0)
                            {
                                colors[l] = 0;
                            }
                        }
                        edgesImage[i][j].rgbtBlue = (BYTE) colors[0];
                        edgesImage[i][j].rgbtRed = (BYTE) colors[1];
                        edgesImage[i][j].rgbtGreen = (BYTE) colors[2];

                    }
                }
                else if (row == height - 1)
                {
                    if (col == 0)
                    {
                        float blueGx = (((float) image[row][col+1].rgbtBlue * 2)
                        + ((float) image[row-1][col+1].rgbtBlue * 1)
                        );

                        float blueGy = (((float) image[row-1][col].rgbtBlue * -2)
                        + ((float) image[row-1][col+1].rgbtBlue * -1)
                        );

                        float redGx = (((float) image[row][col+1].rgbtRed * 2)
                        + ((float) image[row-1][col+1].rgbtRed * 1)
                        );

                        float redGy = (((float) image[row-1][col].rgbtRed * -2)
                        + ((float) image[row-1][col+1].rgbtRed * -1)
                        );


                        float greenGx = (((float) image[row][col+1].rgbtGreen * 2)
                        + ((float) image[row-1][col+1].rgbtGreen * 1)
                        );

                        float greenGy = (((float) image[row-1][col].rgbtGreen * -2)
                        + ((float) image[row-1][col+1].rgbtGreen * -1)
                        );


                        float colors[3] = {round(sqrt(pow(blueGx, 2) + pow(blueGy, 2))),
                        round(sqrt(pow(redGx, 2) + pow(redGy, 2))),
                        round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)))};


                        for (int l = 0; l < 3; l++)
                        {
                            if (colors[l] > 255)
                            {
                            colors[l] = 255;
                            }
                            else if (colors[l] < 0)
                            {
                                colors[l] = 0;
                            }
                        }
                        edgesImage[i][j].rgbtBlue = (BYTE) colors[0];
                        edgesImage[i][j].rgbtRed = (BYTE) colors[1];
                        edgesImage[i][j].rgbtGreen = (BYTE) colors[2];
                    }
                    else if (col == width - 1)
                    {
                        float blueGx = (((float) image[row-1][col-1].rgbtBlue * -1)
                        + ((float) image[row][col-1].rgbtBlue * -2)
                        );

                        float blueGy = (((float) image[row-1][col].rgbtBlue * -2)
                        + ((float) image[row-1][col-1].rgbtBlue * -1)
                        );

                        float redGx = (((float) image[row-1][col-1].rgbtRed * -1)
                        + ((float) image[row][col-1].rgbtRed * -2)
                        );

                        float redGy = (((float) image[row-1][col].rgbtRed * -2)
                        + ((float) image[row-1][col-1].rgbtRed * -1)
                        );


                        float greenGx = (((float) image[row-1][col-1].rgbtGreen * -1)
                        + ((float) image[row][col-1].rgbtGreen * -2)
                        );

                        float greenGy = (((float) image[row-1][col].rgbtGreen * -2)
                        + ((float) image[row-1][col-1].rgbtGreen * -1)
                        );

                        float colors[3] = {round(sqrt(pow(blueGx, 2) + pow(blueGy, 2))),
                        round(sqrt(pow(redGx, 2) + pow(redGy, 2))),
                        round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)))};


                        for (int l = 0; l < 3; l++)
                        {
                            if (colors[l] > 255)
                            {
                            colors[l] = 255;
                            }
                            else if (colors[l] < 0)
                            {
                                colors[l] = 0;
                            }
                        }
                        edgesImage[i][j].rgbtBlue = (BYTE) colors[0];
                        edgesImage[i][j].rgbtRed = (BYTE) colors[1];
                        edgesImage[i][j].rgbtGreen = (BYTE) colors[2];

                    }
                    else
                    {
                        float blueGx = (((float) image[row-1][col-1].rgbtBlue * -1)
                        + ((float) image[row-1][col+1].rgbtBlue * 1)
                        + ((float) image[row][col-1].rgbtBlue * -2)
                        + ((float) image[row][col+1].rgbtBlue * 2)
                        );

                        float blueGy = (((float) image[row-1][col-1].rgbtBlue * -1)
                        + ((float) image[row-1][col].rgbtBlue * -2)
                        + ((float) image[row-1][col+1].rgbtBlue * -1)
                        );

                        float redGx = (((float) image[row-1][col-1].rgbtRed * -1)
                        + ((float) image[row-1][col+1].rgbtRed * 1)
                        + ((float) image[row][col-1].rgbtRed * -2)
                        + ((float) image[row][col+1].rgbtRed * 2)
                        );


                        float redGy = (((float) image[row-1][col-1].rgbtRed * -1)
                        + ((float) image[row-1][col].rgbtRed * -2)
                        + ((float) image[row-1][col+1].rgbtRed * -1)
                        );


                        float greenGx = (((float) image[row-1][col-1].rgbtGreen * -1)
                        + ((float) image[row-1][col+1].rgbtGreen * 1)
                        + ((float) image[row][col-1].rgbtGreen * -2)
                        + ((float) image[row][col+1].rgbtGreen * 2)
                        );

                        float greenGy = (((float) image[row-1][col-1].rgbtGreen * -1)
                        + ((float) image[row-1][col].rgbtGreen * -2)
                        + ((float) image[row-1][col+1].rgbtGreen * -1)
                        );

                        float colors[3] = {round(sqrt(pow(blueGx, 2) + pow(blueGy, 2))),
                        round(sqrt(pow(redGx, 2) + pow(redGy, 2))),
                        round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)))};


                        for (int l = 0; l < 3; l++)
                        {
                            if (colors[l] > 255)
                            {
                            colors[l] = 255;
                            }
                            else if (colors[l] < 0)
                            {
                                colors[l] = 0;
                            }
                        }
                        edgesImage[i][j].rgbtBlue = (BYTE) colors[0];
                        edgesImage[i][j].rgbtRed = (BYTE) colors[1];
                        edgesImage[i][j].rgbtGreen = (BYTE) colors[2];

                    }
                }
                else
                {
                    if (col == 0)
                    {
                        float blueGx = (((float) image[row-1][col+1].rgbtBlue * 1)
                        + ((float) image[row][col+1].rgbtBlue * 2)
                        + ((float) image[row+1][col+1].rgbtBlue * 1)
                        );

                        float blueGy = (((float) image[row-1][col].rgbtBlue * -2)
                        + ((float) image[row-1][col+1].rgbtBlue * -1)
                        + ((float) image[row+1][col].rgbtBlue * 2)
                        + ((float) image[row+1][col+1].rgbtBlue * 1)
                        );

                        float redGx = (((float) image[row-1][col+1].rgbtRed * 1)
                        + ((float) image[row][col+1].rgbtRed * 2)
                        + ((float) image[row+1][col+1].rgbtRed * 1)
                        );

                        float redGy = (((float) image[row-1][col].rgbtRed * -2)
                        + ((float) image[row-1][col+1].rgbtRed * -1)
                        + ((float) image[row+1][col].rgbtRed * 2)
                        + ((float) image[row+1][col+1].rgbtRed * 1)
                        );


                        float greenGx = (((float) image[row-1][col+1].rgbtGreen * 1)
                        + ((float) image[row][col+1].rgbtGreen * 2)
                        + ((float) image[row+1][col+1].rgbtGreen * 1)
                        );

                        float greenGy = (((float) image[row-1][col].rgbtGreen * -2)
                        + ((float) image[row-1][col+1].rgbtGreen * -1)
                        + ((float) image[row+1][col].rgbtGreen * 2)
                        + ((float) image[row+1][col+1].rgbtGreen * 1)
                        );


                        float colors[3] = {round(sqrt(pow(blueGx, 2) + pow(blueGy, 2))),
                        round(sqrt(pow(redGx, 2) + pow(redGy, 2))),
                        round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)))};


                        for (int l = 0; l < 3; l++)
                        {
                            if (colors[l] > 255)
                            {
                            colors[l] = 255;
                            }
                            else if (colors[l] < 0)
                            {
                                colors[l] = 0;
                            }
                        }
                        edgesImage[i][j].rgbtBlue = (BYTE) colors[0];
                        edgesImage[i][j].rgbtRed = (BYTE) colors[1];
                        edgesImage[i][j].rgbtGreen = (BYTE) colors[2];
                    }
                    else if (col == width - 1)
                    {
                        float blueGx = (((float) image[row-1][col-1].rgbtBlue * -1)
                        + ((float) image[row][col-1].rgbtBlue * -2)
                        + ((float) image[row+1][col-1].rgbtBlue * -1)
                        );

                        float blueGy = (((float) image[row-1][col-1].rgbtBlue * -1)
                        + ((float) image[row-1][col].rgbtBlue * -2)
                        + ((float) image[row+1][col].rgbtBlue * 2)
                        + ((float) image[row+1][col-1].rgbtBlue * 1)
                        );

                        float redGx = (((float) image[row-1][col-1].rgbtRed * -1)
                        + ((float) image[row][col-1].rgbtRed * -2)
                        + ((float) image[row+1][col-1].rgbtRed * -1)
                        );

                        float redGy = (((float) image[row-1][col-1].rgbtRed * -1)
                        + ((float) image[row-1][col].rgbtRed * -2)
                        + ((float) image[row+1][col].rgbtRed * 2)
                        + ((float) image[row+1][col-1].rgbtRed * 1)
                        );


                        float greenGx = (((float) image[row-1][col-1].rgbtGreen * -1)
                        + ((float) image[row][col-1].rgbtGreen * -2)
                        + ((float) image[row+1][col-1].rgbtGreen * -1)
                        );

                        float greenGy = (((float) image[row-1][col-1].rgbtGreen * -1)
                        + ((float) image[row-1][col].rgbtGreen * -2)
                        + ((float) image[row+1][col].rgbtGreen * 2)
                        + ((float) image[row+1][col-1].rgbtGreen * 1)
                        );

                        float colors[3] = {round(sqrt(pow(blueGx, 2) + pow(blueGy, 2))),
                        round(sqrt(pow(redGx, 2) + pow(redGy, 2))),
                        round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)))};


                        for (int l = 0; l < 3; l++)
                        {
                            if (colors[l] > 255)
                            {
                            colors[l] = 255;
                            }
                            else if (colors[l] < 0)
                            {
                                colors[l] = 0;
                            }
                        }
                        edgesImage[i][j].rgbtBlue = (BYTE) colors[0];
                        edgesImage[i][j].rgbtRed = (BYTE) colors[1];
                        edgesImage[i][j].rgbtGreen = (BYTE) colors[2];

                    }
                }
            }
        }
    }

    copyArray(height, width, image, edgesImage);

    return;
}

void copyArray(int height, int width, RGBTRIPLE original[height][width], RGBTRIPLE modified[height][width])
{
     for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            original[i][j] = modified[i][j];
        }

    }
}