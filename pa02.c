/*============================================================================
| Assignment: pa02 - Checksum calculation
|              -> the name of the input file,
|              -> the checksum size of either 8, 16, or 32 bits
| Author: Peter Petro  | PE310601 @ ucf.edu | 5448978
| Language: C
| To Compile: gcc -o pa02 pa02.c
| To Execute: c -> ./pa02 inputFilename.txt checksumSize
|                   where inputFilename.txt is the input file
|                   and checksumSize is either 8, 16, or 32
| Note:
|
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
| Class: CIS3360 - Security in Computing - Spring 2025
| Instructor: McAlpin
| Due Date: 03/23/2025
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function prototypes
void printText(const char *buffer, int length); // function for final text printing
unsigned long calcChecksum(const char *buffer, int length, int size); // function to calc checksum

/*
MAIN
*/

// Input the required file name and the checksum size as command line parameters
// NO PROMPT
// The checksum size is a single integer, passed as the second command line argument
int main(int arguments, char *inputArguments[]) {
    if (arguments != 3) {
        fprintf(stderr, "missing file input or checksum size\n");
        return 1;
    }

    int checksumSize = atoi(inputArguments[2]);
    
    // check if the input checksum size is actually 8 or 16 or 32
    if (checksumSize != 8 && checksumSize != 16 && checksumSize != 32) { // error message sent to stderr
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }

    // open file
    FILE *file = fopen(inputArguments[1], "r");
    if (!file) { // error handling
        fprintf(stderr, "Error: Cannot open file %s\n", inputArguments[1]);
        return 1;
    }

    char buffer[10000]; // create a buffer with max character size 10000
    int length = 0; // initalize length
    int readCh = 0; // initalize 

    while ((readCh = fgetc(file)) != EOF && length < 10000) {
        buffer[length++] = (char)readCh; // cast into a character from integer
    }
    fclose(file);

    // Padding
    int pad = 0;
    if (checksumSize == 16 && length % 2 != 0) pad = 1; 
    if (checksumSize == 32 && length % 4 != 0) pad = 4 - (length % 4);

    for (int i = 0; i < pad; i++) // loop to pad with x
        buffer[length++] = 'X';

    printText(buffer, length);

    // get checksum
    unsigned long checksum = calcChecksum(buffer, length, checksumSize);

    // print checksum with given format in assignment pdf
    printf("%2d bit checksum is %8lx for all %4d chars\n", checksumSize, checksum, length);

    return 0; // successful exit
}


// printing function with 80 character formatting limit
void printText(const char *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", buffer[i]);
        if ((i + 1) % 80 == 0)
            printf("\n");
    }
    if (length % 80 != 0)
        printf("\n");
}

// function to compute the check sum value
unsigned long calcChecksum(const char *buffer, int length, int size) {
    unsigned long checksum = 0;
    if (size == 8) {
        for (int i = 0; i < length; i++)
            checksum += (unsigned char) buffer[i];
        return checksum & 0xFF;
    } else if (size == 16) {
        for (int i = 0; i < length; i += 2) {
            unsigned short word = ((unsigned char)buffer[i] << 8);
            if (i + 1 < length)
                word |= (unsigned char)buffer[i + 1];
            else
                word |= 'X';  // padding with x
            checksum += word;
        }
        return checksum & 0xFFFF;
    } else if (size == 32) {
        for (int i = 0; i < length; i += 4) {
            unsigned long word = 0;
            for (int j = 0; j < 4; j++) {
                word <<= 8;
                if (i + j < length)
                    word |= (unsigned char)buffer[i + j];
                else
                    word |= 'X';  // padding with x
            }
            checksum += word;
        }
        return checksum & 0xFFFFFFFF;
    }
    return 0;
}

/*=============================================================================
| I Peter Petro (pe310601) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
