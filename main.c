#include <stdio.h>
#include <errno.h>
#include <err.h>
#include <math.h>
#include "gpu_task.h"

#define AUDIT if(0)

#define ARRAY_SIZE 10000000


int serial() {

    long long int AAA = 1000000000; // size of arrays
    int *data, *output;

    size_t size = AAA * sizeof(int);

    data = (int *) malloc(size);
    if (data == NULL) {
        err(errno, "malloc");
    }
    output = (int *) malloc(size);
    if (output == NULL) {
        err(errno, "malloc");
    }

    for (size_t i = 0; i <= AAA; i++) {
        data[i] = i;
    }

    for (size_t i = 0; i <= AAA; i++) {
        output[i] = data[i] + data[i];
    }

    return 0;
}


int main() {

    cl_int status;
    unsigned int *host_input_data, *host_output_data;
    cl_mem gpu_input_data, gpu_output_data;
    size_t local_size, global_size;

    size_t size = ARRAY_SIZE * sizeof(unsigned int);

    host_input_data = malloc(size);
    if (host_input_data == NULL) {
        err(errno, "malloc");
    }

    host_output_data = malloc(size);
    if (host_output_data == NULL) {
        err(errno, "malloc");
    }

    for (size_t i = 0; i <= ARRAY_SIZE; i++) {
        host_input_data[i] = i;
    }

    GPUTask *gpuTask = get_initialized_gpu_task();

    AUDIT fprintf(stderr, "GPU task fully initializated!\n");

    gpu_input_data = alloc_on_gpu(gpuTask, size, 1, host_input_data);
    gpu_output_data = alloc_on_gpu(gpuTask, size, 0, NULL);
    AUDIT fprintf(stderr, "buffer allocated\n");

    build_kernel(gpuTask, "../program.cl");

    AUDIT fprintf(stderr, "build done\n");


    status = clSetKernelArg(gpuTask->kernel, 0, sizeof(cl_mem), &gpu_input_data);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clSetKernelArg' fail.");
        exit(status);
    }

    status = clSetKernelArg(gpuTask->kernel, 1, sizeof(cl_mem), &gpu_output_data);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clSetKernelArg' fail.");
        exit(status);
    }

    unsigned int dd = ARRAY_SIZE;
    status = clSetKernelArg(gpuTask->kernel, 2, sizeof(const unsigned int), &dd);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clSetKernelArg' fail.");
        exit(status);
    }


    status = clGetKernelWorkGroupInfo(gpuTask->kernel, gpuTask->device_id[0], CL_KERNEL_WORK_GROUP_SIZE,
                                      sizeof(local_size),
                                      &local_size, NULL);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clGetKernelWorkGroupInfo' fail with code: %d.", status);
        exit(status);
    }

    size_t indexSpaceSize[1], workGroupSize[1];
    indexSpaceSize[0] = ((size_t) ARRAY_SIZE / local_size) * local_size;;
    workGroupSize[0] = local_size;


    //AUDIT fprintf(stderr, "GL: %lu, LS: %lu\n", global_size, workGroupSize);

    status = clEnqueueNDRangeKernel(gpuTask->command_queue, gpuTask->kernel, 1, NULL, indexSpaceSize, workGroupSize, 0,
                                    NULL, NULL);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clEnqueueNDRangeKernel' fail with code: %d.", status);
        exit(status);
    }

    block_gpu_until_completion(gpuTask);

    clEnqueueReadBuffer(gpuTask->command_queue, gpu_output_data, CL_TRUE, 0, size, host_output_data, 0, NULL, NULL);

    AUDIT for (int i = 0; i <= ARRAY_SIZE; i++) {
            printf("%d\n", host_output_data[i]);
        }

    return 0;
}

