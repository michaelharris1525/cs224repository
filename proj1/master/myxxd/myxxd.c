#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBER_ARGS 1


void printing_charactervalue(unsigned char x) {
  int array[8];
    for(int i=7; i >= 0; --i) {
        if (x % 2 == 1) {
        //store a 1 bit
            array[i] = 1;
            // printf("%d", array[i]);
        }
        else {
        //store a 0 bit
            array[i] = 0;
            // printf("%d", array[i]);
        }
        x = x / 2;
    }
    for(int i=0; i < 8; i++) {
        printf("%d", array[i]);
    }
}

/**
 * Parses the command line.
 *
 * argc: the number of items on the command line (and length of the
 *       argv array) including the executable
 * argv: the array of arguments as strings (char* array)
 * bits: the integer value is set to TRUE if bits output indicated
 *       outherwise FALSE for hex output
 *
 * returns the input file pointer (FILE*)
 **/
FILE *parseCommandLine(int argc, char **argv, int *bits) {
  if (argc > 2) {
    printf("Usage: %s [-b|-bits]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }

  if (argc == 2 &&
      (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0)) {
    *bits = TRUE;
  } else {
    *bits = FALSE;
  }

  return stdin;
}

/**
 * Writes data to stdout in hexadecimal.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsHex(unsigned char *data, size_t size) {
  // printing_charactervalue(data);
  for(size_t i = 0; i < size; i++) {
    printf("%02x", data[i]);
    if(i%2==1 && i != size-1) {
      printf(" ");
    }
  }
  // printf("\n");
}

/**
 * Writes data to stdout as characters.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsChars(unsigned char *data, size_t size) {
  // printf("TODO 2: printDataAsChars (3)");
  for(size_t i = 0; i <size; i++) {
    if(data[i] >= 32 && data[i] <= 126) {
      printf("%c", data[i]);
    }
    else {
      printf(".");
    }
  }
  printf("\n");
}

void readAndPrintInputAsHex(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 16, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsHex(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 16, input);
  }
}

/**
 * Bits output for xxd.
 *
 * See myxxd.md for details.
 *
 * input: input stream
 **/
void readAndPrintInputAsBits(FILE *input) {
  // printf("TODO 3: readAndPrintInputAsBits\n");
  unsigned char buffer[16]; // Buffer to read data
    size_t bytesRead; // Number of bytes read

    // Read data in chunks of 16 bytes
    while ((bytesRead = fread(buffer, 1, 16, input)) > 0) {
        // Iterate over each byte read
        for (size_t i = 0; i < bytesRead; i++) {
            // Print each byte as bits
            for (int j = 7; j >= 0; j--) {
                printf("%d", (buffer[i] >> j) & 1); // Print the j-th bit of the byte
            }
            printf(" "); // Separate bytes with a space
        }
        printf("\n"); // Move to the next line after printing each chunk
    }
}

int main(int argc, char **argv) {
  int bits = FALSE;
  FILE *input = parseCommandLine(argc, argv, &bits);

  if (bits == FALSE) {
    readAndPrintInputAsHex(input);
  } else {
    readAndPrintInputAsBits(input);
  }
  return 0;
}
