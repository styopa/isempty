/*
Copyright 2018 Styopa Semenukha
This file is part of isempty, see COPYING
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "isempty.h"

int main(const int argc, char * const argv[])
{
    int flags, opt;
    unsigned char byte = 0;
    const char *file_name;

    while ((opt = getopt(argc, argv, "b:")) != -1) {
        switch (opt) {
        case 'b':
            byte = (unsigned char) atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-b 0] FILE_NAME\n", argv[0]);
            exit(ERROR_OPTIONS);
        }
    }

    printf("byte = %hhi\n", byte);

    if (optind >= argc) {
        fprintf(stderr, "File name required\n");
        exit(ERROR_OPTIONS);
    }

    file_name = argv[optind];
    printf("File name: %s\n", file_name);
}
