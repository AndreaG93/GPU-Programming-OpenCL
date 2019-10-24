//
// Created by andrea on 19/10/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "error.h"

#define FILE_NOT_FOUND 1




#define SUCCESS = 0













void check_errno(char* function_name) {

    fflush(stdout);

    if (errno != 0) {
        fprintf(stderr, "::[ERROR]::\n\t ErrNo: %d\n\t Function: %s\n\t Message: %s\n.", errno, function_name,
                strerror(errno));
        exit(errno);
    }
}

void exit_printing_error(int exit_code, char* function_name, char* message) {

    fprintf(stderr, "::[ERROR]::\n\t ErrNo: %d\n\t Function: %s\n\t Message: %s\n.", exit_code, function_name,
            message);
    exit(exit_code);
}





void exit_printing_error_s(Error* error) {
    exit_printing_error(error->exit_code, error->function_name, error->message);
}

Error* new_error(int exit_code, char* function_name, char* message) {

    Error* output = malloc(sizeof(Error));

    if (output == NULL) {
        exit_printing_error(EXIT_FAILURE, "malloc", "null pointer");
    } else {
        output->exit_code = exit_code;
        output->function_name = function_name;
        output->message = message;
    }

    return output;
}


void CheckError(Error* input) {

    if (input != NULL) {
        exit_printing_error(input->exit_code, input->function_name, input->message);
    }
}




