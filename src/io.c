#include "include/io.h"
#include <stdlib.h>
#include <stdio.h>



char* get_file_contents(const char* filepath)
{
    char* buffer = 0;
    long length;
    FILE* f = fopen(filepath, "rb");

    if(f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = calloc(length,length);
        if(buffer)
        fread(buffer, 1, length, f);
        fclose(f);
        return buffer;
    }
    printf("Error reading file %s\n", filepath);
    exit(2);
}

// char* get_file_contents(const char* filepath)
// {
//     char* buffer = 0;
//     long length;
//     FILE* f = fopen(filepath, "rb");

//     if (f) {
//         fseek(f, 0, SEEK_END);
//         length = ftell(f);
//         fseek(f, 0, SEEK_SET);
//         buffer = calloc(length + 1, 1);  // Fixed allocation
//         if (buffer)
//             fread(buffer, 1, length, f);
//         fclose(f);
//         return buffer;
//     }

//     // Print error but return NULL instead of exiting
//     fprintf(stderr, "Error reading file: %s\n", filepath);
//     return NULL;
// }
