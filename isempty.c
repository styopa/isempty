/*
Copyright 2018 Styopa Semenukha
This file is part of isempty, see COPYING
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "isempty.h"

void print_usage(const char *path)
{
    int buf_size = sysconf(_SC_PAGESIZE);
    fprintf(stderr, "Usage: %s [-b 0] [-s %li] FILE_NAME\n", path, buf_size);
}

int get_chunk_size(off_t file_size, int buf_size, int percent, int *n_chunks)
{
    int bytes_to_read;

    bytes_to_read = file_size * percent / 100;
    if (!bytes_to_read) {
        bytes_to_read = file_size;
    }
    *n_chunks = div_ceil(bytes_to_read, buf_size);

    return div_ceil(file_size, *n_chunks);
}

int is_empty(const char *path, unsigned char byte, int percent, int buf_size)
{
    FILE *file;
    unsigned char *buffer;
    struct stat stat_buf;
    int n_chunks, result;
    size_t bytes_read;

    if ( !(file = fopen(path, "r")) ) {
        result = RESULT_IO_ERROR;
        goto fail;
    }

    if (fstat(fd, &stat_buf)) {
        result = RESULT_IO_ERROR;
        goto fail;
    }

    chunk_size = get_chunk_size(stat_buf.st_size, buf_size, percent, &n_chunks);
    buffer = (unsigned char *) malloc(buf_size);
    if (!buffer) {
        result = RESULT_OOM;
        goto fail;
    }

    for (int i = 0; i < n_chunks; i++) {
        if (fseek(file, i * chunk_size, SEEK_SET)) {
            result = RESULT_IO_ERROR;
            goto fail;
        }

        bytes_read = fread(buffer, 1, buf_size, file);
        if (ferror(file)) {
            result = RESULT_IO_ERROR;
            goto fail;
        }

        for (unsigned char *j = buffer; j < bytes_to_read; j++) {
            if (j != byte) {
                result = RESULT_NOT_EMPTY;
                goto end;
            }
        }
    }

    result = RESULT_EMPTY;
    goto end;

fail:
    fprintf(stderr, "%s\n", strerror(errno));

end:
    if (file) {
        fclose(file);
    }

    return(result);
}

int main(int argc, char * const argv[])
{
    int opt, result;
    unsigned char byte = 0;
    int buf_size = sysconf(_SC_PAGESIZE);

    while ((opt = getopt(argc, argv, "b:")) != -1) {
        switch (opt) {
        case 'b':
            byte = (unsigned char) atoi(optarg);
            break;
        case 's':
            buf_size = (int) atoi(optarg);
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
