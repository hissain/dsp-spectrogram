#include "arm_math.h"
#include "arm_math_types.h"

int test_kalman_filter(float32_t *signal, int len);
void test_spline_linear_interpolation(float32_t x[], int len, int nlen, float32_t fs);
void test_spline_cubic_interpolation(float32_t x[], int len, int nlen, float32_t fs);
void spline_cubic_interpolation(float32_t *x_in, float32_t *y_in, int len_in, float32_t *x_out, float32_t *y_out, int *len_out);