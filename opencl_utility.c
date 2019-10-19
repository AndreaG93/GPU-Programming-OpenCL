//
// Created by andrea on 18/10/19.
//

#include "opencl_utility.h"
#include <CL/cl.h>
#include <stdio.h>
#include <pngconf.h>






typedef struct {
    cl_context open_cl_context;
    cl_device_id open_cl_device_id;
} open_cl_computation_unit;





/**
 * A set of OpenCL devices use by the host to execute kernels.
 *
 * @return
 */
cl_device_id build_context(Error *err, open_cl_computation_unit* unit) {

    cl_platform_id platforms;
    cl_uint num_platforms;
    cl_int error;


    /* Identify a platform */
    error = clGetPlatformIDs(1, &platforms, &num_platforms);
    if (error == CL_SUCCESS) {

        err = new_error(EXIT_FAILURE, "clGetPlatformIDs", "platforms and number of platforms is NULL or the number of entries is 0.");
        return 0;
    }

    error = clGetDeviceIDs(platforms, CL_DEVICE_TYPE_GPU, 1, &(unit->open_cl_device_id), NULL);
    if (error == CL_INVALID_PLATFORM) {

        err = new_error(EXIT_FAILURE, "clGetDeviceIDs", "platform is not valid");
        return 0;

    } else if (error == CL_INVALID_VALUE) {

        err = new_error(EXIT_FAILURE, "clGetDeviceIDs", "number of devices and devices are NULL");
        return 0;

    } else if (error == CL_INVALID_DEVICE_TYPE) {

        err = new_error(EXIT_FAILURE, "clGetDeviceIDs", "the device is not a valid value");
        return 0;

    } else if (error == CL_DEVICE_NOT_FOUND) {

        err = new_error(EXIT_FAILURE, "clGetDeviceIDs", "no matching OpenCL of device_type was found");
        return 0;

    } else {
        return 0;
    }
}

