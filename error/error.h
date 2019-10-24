//
// Created by andrea on 19/10/19.
//

#ifndef UNTITLED_ERROR_H
#define UNTITLED_ERROR_H

#define c_err unsigned int

#define MEMORY_ALLOCATION_FAILURE 1
#define FILE_NOT_FOUND 2

typedef struct {
    int exit_code;
    char* function_name;
    char* message;
} Error;

void check_errno(char* function_name);
void exit_printing_error(int exit_code, char* function_name, char* message);

#endif //UNTITLED_ERROR_H
