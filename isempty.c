/*
Copyright 2018 Styopa Semenukha
This file is part of isempty, see COPYING
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "isempty.h"

void print_usage(const char *path)
{
    fprintf(stderr, "Usage: %s [-b 0] FILE_NAME\n", path);
}

int is_empty(const unsigned char byte, const char *path)
{
    FILE *file;

    file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "%s\n", strerror(errno));
        return RESULT_IO_ERROR;
    }

    fclose(file);
}

int main(const int argc, char * const argv[])
{
    int opt, result;
    unsigned char byte = 0;

    while ((opt = getopt(argc, argv, "b:")) != -1) {
        switch (opt) {
        case 'b':
            byte = (unsigned char) atoi(optarg);
            break;
        default:
            print_usage(argv[0]);
            exit(RESULT_BAD_OPTIONS);
        }
    }

    if (optind >= argc) {
        print_usage(argv[0]);
        exit(RESULT_BAD_OPTIONS);
    } else {
        result = is_empty(byte, argv[optind]);
        exit(result);
    }
}
