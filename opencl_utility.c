//
// Created by andrea on 18/10/19.
//

#include "opencl_utility.h"
#include "error/error.h"
#include <CL/cl.h>
#include <stdio.h>


OpenCLComputationUnit *NewOpenCLComputationUnit() {

    OpenCLComputationUnit *output = malloc(sizeof(OpenCLComputationUnit));
    if (output == NULL) {

        exit_printing_error(EXIT_FAILURE, "malloc", "Null pointer");

    } else {

        output->device_type = CL_DEVICE_TYPE_CPU;
    }

    return output;
}


void OpenCLPlatformConfiguration(OpenCLComputationUnit *input, Error **err) {

    if (clGetPlatformIDs(1, &(input->open_cl_platform_id), &(input->num_of_open_cl_platforms)) != CL_SUCCESS) {
        *err = new_error(EXIT_FAILURE, "clGetPlatformIDs", "Unable to get platform IDs");
    } else {
        *err = NULL;
    }
}

void OpenCLDeviceConfiguration(OpenCLComputationUnit *input, Error **err) {

    cl_int error = clGetDeviceIDs(input->open_cl_platform_id, input->device_type, 1, &(input->open_cl_device_id),
                                  &(input->num_of_open_cl_devices));

    switch (error) {
        case CL_INVALID_PLATFORM:
            *err = new_error(EXIT_FAILURE, "clGetDeviceIDs", "Platform is not valid.");
            break;
        case CL_INVALID_DEVICE_TYPE:
            *err = new_error(EXIT_FAILURE, "clGetDeviceIDs", "The device is not a valid value.");
            break;
        case CL_DEVICE_NOT_FOUND:
            *err = new_error(EXIT_FAILURE, "clGetDeviceIDs", "No matching OpenCL of specified device type was found.");
            break;
        case CL_INVALID_VALUE:
            *err = new_error(EXIT_FAILURE, "clGetDeviceIDs", "Number of devices and devices are NULL.");
            break;
        default:
            *err = NULL;
    }
}

void OpenCLContextConfiguration(OpenCLComputationUnit *input, Error **err) {

    cl_int error;
    cl_context_properties properties[3];

    properties[0] = CL_CONTEXT_PLATFORM;
    properties[1] = (cl_context_properties) input->open_cl_platform_id;
    properties[2] = 0;

    input->open_cl_context = clCreateContext(properties, 1, &(input->open_cl_device_id), NULL, NULL, &error);

    switch (error) {
        case CL_INVALID_PLATFORM:
            *err = new_error(EXIT_FAILURE, "clCreateContext", "Platform is not valid.");
            break;
        case CL_DEVICE_NOT_AVAILABLE:
            *err = new_error(EXIT_FAILURE, "clCreateContext","The device in the device_id list is currently unavailable.");
            break;
        case CL_OUT_OF_HOST_MEMORY:
            *err = new_error(EXIT_FAILURE, "clCreateContext", "The host is unable to allocate OpenCL resources.");
            break;
        case CL_INVALID_VALUE:
            *err = new_error(EXIT_FAILURE, "clCreateContext", "Number of devices and devices are NULL.");
            break;
        default:
            *err = NULL;
    }
}

void OpenCLCommandQueueConfiguration(OpenCLComputationUnit *input, Error **err) {

    cl_int error;

    input->command_queue = clCreateCommandQueueWithProperties(input->open_cl_context, input->open_cl_device_id, 0, &error);

    switch (error) {
        case CL_INVALID_CONTEXT:
            *err = new_error(EXIT_FAILURE, "clCreateCommandQueueWithProperties", "The context is not valid.");
            break;
        case CL_INVALID_DEVICE:
            *err = new_error(EXIT_FAILURE, "clCreateCommandQueueWithProperties","Either the device is not valid or it is not associated with the context.");
            break;
        case CL_INVALID_QUEUE_PROPERTIES:
            *err = new_error(EXIT_FAILURE, "clCreateCommandQueueWithProperties", "The device does not support the properties specified in the properties list.");
            break;
        case CL_INVALID_VALUE:
            *err = new_error(EXIT_FAILURE, "clCreateCommandQueueWithProperties", "The properties list is not valid.");
            break;
        case CL_OUT_OF_HOST_MEMORY:
            *err = new_error(EXIT_FAILURE, "clCreateContext", "The host is unable to allocate OpenCL resources.");
            break;
        default:
            *err = NULL;
    }
}

void ExecuteComputationOnGPU(OpenCLComputationUnit *input) {

    Error *err;

    OpenCLPlatformConfiguration(input, &err);
    CheckError(err);

    OpenCLDeviceConfiguration(input, &err);
    CheckError(err);

    OpenCLContextConfiguration(input, &err);
    CheckError(err);

    OpenCLCommandQueueConfiguration(input, &err);
    CheckError(err);

}