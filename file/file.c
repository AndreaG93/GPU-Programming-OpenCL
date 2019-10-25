//
// Created by andrea on 24/10/19.
//

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include "file.h"

File *read_all(char *filename) {

    File *output;
    int file_descriptor;

    if (access(filename, R_OK) != 0) {
        err(EXIT_FAILURE, "access");
    }

    file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1)
        err(EXIT_FAILURE, "open");

    output = malloc(sizeof(File));
    if (output == NULL)
        err(EXIT_FAILURE, "malloc");

    output->file_stat = malloc(sizeof(stat));
    if (output->file_stat == NULL)
        err(EXIT_FAILURE, "malloc");


    if (fstat(file_descriptor, output->file_stat) != 0)
        err(EXIT_FAILURE, "fstat");

    output->data = malloc(output->file_stat->st_size);
    if (output->data == NULL)
        err(EXIT_FAILURE, "malloc");

    if (read(file_descriptor, output->data, output->file_stat->st_size) != output->file_stat->st_size)
        err(EXIT_FAILURE, "read");

    if (close(file_descriptor) == -1)
        err(EXIT_FAILURE, "close");

    return output;
}