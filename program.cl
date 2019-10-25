__kernel void square(__global float* input, __global float* output, size_t count) {
	size_t i = get_global_id(0);

	if (i < count) {
		output[i]=input[i]*input[i];
	}
}