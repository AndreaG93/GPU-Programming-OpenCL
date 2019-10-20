//
// Created by andrea on 19/10/19.
//

#ifndef UNTITLED_ERROR_H
#define UNTITLED_ERROR_H

typedef struct {
    int exit_code;
    char* function_name;
    char* message;
} Error;

Error* new_error(int exit_code, char* function_name, char* message);
void CheckError(Error* input);

void exit_printing_error_s(Error* error);
void exit_printing_error(int exit_code, char* function_name, char* message);

#endif //UNTITLED_ERROR_H
