/*
 * A small program to translate the gibberish output of the KONIG barcode scanner into ISBN format.
 *
 * (c) 2022, PulSR SAS
 * SPDX-License-Identifier: MIT
 */


#include <stdio.h>
#include <stdlib.h>

unsigned char translation_table[10] = {
    224, /* 0 */
    38,  /* 1 */
    233, /* 2 */
    34,  /* 3 */
    39,  /* 4 */
    40,  /* 5 */
    45,  /* 6 */
    232, /* 7 */
    95,  /* 8 */
    231, /* 9 */
};

FILE * output = NULL;

 int main(void)
 {
    #define LINE_MAX_SIZE 42
    size_t line_max_size = LINE_MAX_SIZE; 
    char * string = (char *) malloc (line_max_size);
    // read line-by-line
    size_t byte_read = 0;
    while (byte_read != -1)
    {
        output = fopen("./result.txt", "a+b");
        if (output == NULL) 
            return EXIT_FAILURE;
        byte_read = getline( &string, &line_max_size, stdin);
        for (int i = 0; i < byte_read; i++) {
            for (int j = 0; j < 10; j++) {
                unsigned char c = string[i];
                if (c == translation_table[j]) {
                    fprintf(output, "%u", j);
                }
            }
        }
        fprintf(output, "\r\n");
        fclose(output);
    }
    free(string);
    return EXIT_SUCCESS; // goodbye
 }
 