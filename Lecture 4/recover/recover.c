#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int getExtension(char *filename);

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{

    // check for argument counts
    if (argc != 2)
    {
        printf("Invalid\n");
        return 1;
    }



    char *filename = argv[1];





    // file extension validation
    if (!getExtension(filename))
    {
        printf("Invalid extension\n");
        return 1;
    }
    // ----- start the real logic here -----

    FILE *file = fopen(argv[1], "r"); // open file pointer

    // check if file pointer is not null
    if (file == NULL)
    {
        return 1;
    }

    BYTE *buffer = malloc(BLOCK_SIZE * sizeof(uint8_t));

    if (buffer == NULL)
    {
        return 1;
    }

    int filenameCounter = 0;
    char file_Name[8];
    FILE *img = NULL;

    while(fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE) // read every 512 bytes of memorycard into buffer pointer and check if not the end of the memmory.
    {
        //while(fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE) while(!feof(file))

        //fread(buffer, 1, BLOCK_SIZE, file);


        //FILE *img = fopen(fileName, "a"); // try to open file pointer with append of filename.

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
        && (buffer[3] & 0xf0) == 0xe0) // check if header of JPEG.
        {
            sprintf(file_Name, "%03i.jpg", filenameCounter);

            if (filenameCounter == 0)
            {
                img = fopen(file_Name, "w"); //generate a new file.

            }
            else
            {
                fclose(img);
                img = fopen(file_Name, "a");

            }

            fwrite(buffer, 1, BLOCK_SIZE, img);
            filenameCounter++; // set counter


        }

        else
        {
            if (img != NULL) // check null pointer
            {
                fwrite(buffer, 1, BLOCK_SIZE, img); // write this chunk of memmory
            }


        }


    }

    free(buffer);
    fclose(file);
    fclose(img);
    return 0;
}







// file extension validation

int getExtension(char *filename)
{
    int counter = 0;

    while(*(filename + counter) != '.')
    {
        counter++;
    }

    if (*(filename + counter + 1) != 'r' &&
    *(filename + counter + 2) != 'a' &&
    *(filename + counter + 3) != 'w')
    {

        return 0;
    }

    return 1;

}





// ______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________





 //     if (img == NULL) // if img pointer is null then there is no such file with such filename.
        //     {

        //         img = fopen(fileName, "w"); //generate a new file.
        //         fwrite(buffer, 1, BLOCK_SIZE, img);
        //         filenameCounter++;
        //     }
        //     else
        //     {
        //         fclose(img);
        //         img = fopen(fileName, "w");
        //         fwrite(buffer, 1, BLOCK_SIZE, img);
        //         filenameCounter++;
        //     }


        // }
        // else // continue writing previous byte chunks of file
        // {
        //     // sprintf(fileName, "%03i.jpg", filenameCounter);
        //     // FILE *img = fopen(fileName, "a");
        //     fwrite(buffer, 1, BLOCK_SIZE, img);