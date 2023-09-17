// Modifies the volume of an audio file
// ./volume INPUT.wav OUTPUT.wav 2.0
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // check if uppercase or lowercase filename is passed



    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        int counter = 0;
        while (argv[1][counter] != '.')
        {
            argv[1][counter] = argv[1][counter] + 32; // convert charachters from uppercase to lowercase
            counter++;
        }

        input = fopen(argv[1], "r");
        if (input == NULL)
        {
            printf("Could not open file.\n");
            return 1;
        }

    }



    // printf("%lu\n", sizeof(*input));


    FILE *output = fopen(argv[2], "w");

    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);



    // TODO: Copy header from input file to output file

    uint8_t header[HEADER_SIZE];
    int16_t buffer;

    int n = fread(header, sizeof(uint8_t), HEADER_SIZE, input);

    // printf("%i\n", n);

    fwrite(header, sizeof(uint8_t), n, output);

    fclose(output);

    output = fopen(argv[2], "a");


    while(fread(&buffer, sizeof(int16_t), 1, input) != 0)
    {

        buffer = buffer * factor;

        fwrite(&buffer, sizeof(int16_t), 1, output);
    }




    // Close files
    fclose(input);
    fclose(output);
}


