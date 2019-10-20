//
// Created by andrea on 18/10/19.
//

#ifndef UNTITLED_OPENCL_UTILITY_H
#define UNTITLED_OPENCL_UTILITY_H

#include <CL/cl.h>

typedef struct {

    cl_device_type device_type;

    cl_platform_id open_cl_platform_id;
    cl_uint num_of_open_cl_platforms;

    cl_device_id open_cl_device_id;
    cl_uint num_of_open_cl_devices;

    cl_context open_cl_context;

    cl_command_queue command_queue

} OpenCLComputationUnit;

OpenCLComputationUnit *NewOpenCLComputationUnit();
void ExecuteComputationOnGPU(OpenCLComputationUnit *input);

#endif //UNTITLED_OPENCL_UTILITY_H
