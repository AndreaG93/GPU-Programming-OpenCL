//
// Created by andrea on 24/10/19.
//

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "../error/error.h"

typedef struct {
    void *data;
    struct stat *file_stat;
} c_file;

c_file *alloc_c_file() {

    errno = 0;
    c_file *output = malloc(sizeof(c_file));
    if (output == NULL) {
        perror("malloc");
    }

    return output;
}


c_file *read_data_and_properties_from_file(char *pathname, c_err *error) {

    int file_descriptor;
    c_file *output = alloc_c_file();

    if (access(pathname, R_OK) != 0)
        perror("access");

    file_descriptor = open(pathname, O_RDONLY);
    if (file_descriptor == -1) {
        perror("open");
    }

    if (fstat(file_descriptor, output->file_stat) != 0) {
        perror("fstat");
    }

    output->data = calloc(output->file_stat->st_size, sizeof(char));
    if (output->data == NULL) {
        perror("calloc");
    }


    for (;;) {
        size_t read_byte = read(file_descriptor, output->data, output->file_stat->st_size);

        if (read_byte == 0 || read_byte == output->file_stat->st_size)
            break;
        else if (read_byte == -1) {
            perror("close");
        }
    }

    if (close(file_descriptor) == -1) {
        perror("close");
    }

    return output;
}
