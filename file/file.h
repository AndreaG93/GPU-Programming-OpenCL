//
// Created by andrea on 24/10/19.
//

#ifndef UNTITLED_FILE_H
#define UNTITLED_FILE_H

typedef struct {
    void *data;
    struct stat *file_stat;
} File;

File *read_all(char *filename);

#endif //UNTITLED_FILE_H
