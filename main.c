#include <stdio.h>
#include <error.h>
#include <errno.h>
#include "opencl_utility.h"

int main() {
    //OpenCLComputationUnit* x = NewOpenCLComputationUnit();
    //ExecuteComputationOnGPU(x);
    errno = 0;
    if (malloc(9999999 * 99999999) == NULL) {
        error(ESRCH, ESRCH, "test %s", "prova");
        //perror("sdsa");
    }
    return 0;
}