#include <stdio.h>
#include "opencl_utility.h"

int main() {
    OpenCLComputationUnit* x = NewOpenCLComputationUnit();
    ExecuteComputationOnGPU(x);

    return 0;
}