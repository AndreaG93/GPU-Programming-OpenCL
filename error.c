//
// Created by andrea on 19/10/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "error.h"

void exit_printing_error(int exit_code, char* function_name, char* message){

    fprintf(stderr, "[ERROR] Function: %s\n        Message: %s.\n Error number: %d", function_name, message, strerror(errno));
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






