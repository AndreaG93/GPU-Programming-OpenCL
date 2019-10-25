//
// Created by andrea on 18/10/19.
//

#ifndef UNTITLED_GPU_TASK_H
#define UNTITLED_GPU_TASK_H

#include <CL/cl.h>

typedef struct {

    cl_uint num_of_platforms;
    cl_uint num_of_devices;

    cl_platform_id* platform_id;
    cl_device_id* device_id;

    cl_program program;
    cl_context context;
    cl_kernel kernel;
    cl_command_queue command_queue;

} GPUTask;

GPUTask *get_initialized_gpu_task();
void build_kernel(GPUTask *input, char *filename);
void *alloc_on_gpu(GPUTask *gpuTask, size_t size, int read_only, void *host_data);
void block_gpu_until_completion(GPUTask *gpuTask);

#endif //UNTITLED_GPU_TASK_H
