//
// Created by andrea on 18/10/19.
//

#include "gpu_task.h"
#include "file/file.h"
#include <CL/cl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <err.h>

const char *KernelSource = "__kernel void square(                    \n"
                           "   __global float* input,                \n"
                           "   __global float* output,               \n"
                           "   const unsigned int count)             \n"
                           "{                                        \n"
                           "   int i = get_global_id(0);             \n"
                           "   if(i < count)                         \n"
                           "       output[i] = input[i] * input[i];  \n"
                           "}                                        \n"
                           "\n";


void build_kernel(GPUTask *gpuTask, char *filename) {

    cl_int status;
    //File *program_file = read_all(filename);

    size_t size = strlen(KernelSource);
    gpuTask->program = clCreateProgramWithSource(gpuTask->context, 1, (const char **) &KernelSource,
                                               &size, &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clCreateProgramWithSource' fail.");
        exit(status);
    }

    status = clBuildProgram(gpuTask->program, gpuTask->num_of_devices, gpuTask->device_id, NULL, NULL, NULL);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clBuildProgram' fail.");
        exit(status);
    }

    gpuTask->kernel = clCreateKernel(gpuTask->program, "square", &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clCreateKernel' fail.");
        exit(status);
    }
}

void *alloc_on_gpu(GPUTask *gpuTask, size_t size, int read_only, void *host_data) {

    cl_mem output;
    cl_int status;

    output = clCreateBuffer(gpuTask->context, (read_only == 1) ? CL_MEM_READ_ONLY : CL_MEM_WRITE_ONLY, size, NULL,
                            &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clCreateBuffer' fail with code %d.", status);
        exit(status);
    }

    if (host_data != NULL) {
        status = clEnqueueWriteBuffer(gpuTask->command_queue, output, CL_TRUE, 0, size, host_data, 0, NULL,
                                      NULL);
        if (status != CL_SUCCESS) {
            fprintf(stderr, "'clEnqueueWriteBuffer' fail with code %d.", status);
            exit(status);
        }
    }

    return output;
}

GPUTask *get_initialized_gpu_task() {

    cl_int status;
    //cl_context_properties properties[3];

    GPUTask *output = malloc(sizeof(GPUTask));
    if (output == NULL)
        err(EXIT_FAILURE, "malloc");

    status = clGetPlatformIDs(0, NULL, &output->num_of_platforms);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clGetPlatformIDs' fail.");
        exit(status);
    }

    output->platform_id = malloc(output->num_of_platforms * sizeof(cl_platform_id));
    if (output->platform_id == NULL)
        err(EXIT_FAILURE, "malloc");


    status = clGetPlatformIDs(output->num_of_platforms, output->platform_id, NULL);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clGetPlatformIDs' fail.");
        exit(status);
    }


    /******************/




    status = clGetDeviceIDs(output->platform_id[0], CL_DEVICE_TYPE_ALL, 0, NULL, &output->num_of_devices);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clGetDeviceIDs' fail.");
        exit(status);
    }

    output->device_id = malloc(output->num_of_devices * sizeof(cl_device_id));
    if (output->device_id == NULL)
        err(EXIT_FAILURE, "malloc");

    status = clGetDeviceIDs(output->platform_id[0], CL_DEVICE_TYPE_ALL, output->num_of_devices, output->device_id,
                            NULL);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clGetDeviceIDs' fail.");
        exit(status);
    }



    //properties[0] = CL_CONTEXT_PLATFORM;
    //properties[1] = (cl_context_properties) output->platform_id;
    //properties[2] = 0;

    output->context = clCreateContext(NULL, output->num_of_devices, output->device_id, NULL, NULL, &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clCreateContext' fail.");
        exit(status);
    }

    output->command_queue = clCreateCommandQueueWithProperties(output->context, output->device_id[0], 0, &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clCreateCommandQueueWithProperties' fail.");
        exit(status);
    }

    return output;
}


void block_gpu_until_completion(GPUTask *gpuTask) {

    cl_int status;

    status = clFinish(gpuTask->command_queue);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "'clFinish' fail.");
        exit(status);
    }
}

void free_gpu_task(GPUTask *input) {

    clReleaseKernel(input->kernel);
    clReleaseCommandQueue(input->command_queue);
    clReleaseProgram(input->program);
    clReleaseContext(input->context);
}