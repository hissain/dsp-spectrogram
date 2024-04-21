#include <stdio.h>
#include <stdlib.h>

#include "spect_utils.h"
#include "dsp.h"

void spline_cubic_interpolation(float32_t *x_in, float32_t *y_in, int len_in, float32_t *x_out, float32_t *y_out, int *len_out){

}


void export_spline(float32_t *data, int len, char file[100]){
    // Save PSD data to a file
    FILE *fp;
    fp = fopen(file, "w");
    if (fp != NULL) {
        for (int i = 0; i < len; i++){
            fprintf(fp, "%f \n", data[i]);
        }
        fclose(fp);
    } else {
        printf("Error opening file for writing\n");
    }
}

void test_spline_cubic_interpolation(float32_t x[], int len, int nlen, float32_t fs){

// Calculate the time step for the input data
    float32_t df = 1.0f / fs;

    // Allocate memory for input x and y arrays
    float32_t x_in[len];
    float32_t y_in[len];

    // Populate input x and y arrays
    for(int i = 0; i < len; i++) {
        x_in[i] = df * i;
        y_in[i] = x[i];
    }

    // Calculate the time step for the output data
    float32_t df_n = (x_in[len - 1] - x_in[0]) / (nlen - 1);

    // Allocate memory for output x and y arrays
    float32_t x_out[nlen];
    float32_t y_out[nlen];

    // Generate output x values
    for(int i = 0; i < nlen; i++) {
        x_out[i] = df_n * i;
    }

    // Print some debugging information
    printf("df: %lf\n", (double)df);
    printf("df_n: %lf\n", (double)df_n);
    printf("nlen: %d\n", nlen);

    // Allocate memory for coefficient and buffer arrays
    float32_t coef[3 * len];
    float32_t buff[2 * len];

    // Initialize spline instance
    arm_spline_instance_f32 S;
    arm_spline_init_f32(&S, ARM_SPLINE_PARABOLIC_RUNOUT, x_in, y_in, len, coef, buff);

    // Perform spline interpolation
    arm_spline_f32(&S, x_out, y_out, nlen);

    print_array(x_out, nlen);
    print_array(y_out, nlen);

    export_spline(x_in, len, "python/spline_x_in.csv");
    export_spline(y_in, len, "python/spline_y_in.csv");
    export_spline(x_out, nlen, "python/spline_x_out.csv");
    export_spline(y_out, nlen, "python/spline_y_out.csv");
}

void test_spline_linear_interpolation(float32_t x[], int len, int nlen, float32_t fs) {

    // Define input and output arrays
    float32_t x_in[len];
    float32_t y_in[len];

    // Calculate the time step for the input data
    float32_t df = 1.0f / fs;

    // Populate input x and y arrays
    for(int i = 0; i < len; i++) {
        x_in[i] = df * i;
        y_in[i] = x[i];
    }

    float32_t scale = 1.0f * nlen / len;

    // Initialize CMSIS DSP interpolation instance
    arm_linear_interp_instance_f32 s;
    s.x1 = 0.0f; // Assuming x1 is 0 based on provided API
    s.xSpacing = df; // Assuming xSpacing is df based on provided API
    s.nValues = len; // Number of input values
    s.pYData = y_in; // Pointer to input y values

    float32_t x_interpolated[nlen]; // Interpolated x values
    float32_t y_interpolated[nlen]; // Interpolated y values

    // Perform linear interpolation
    for (int i = 0; i < nlen; i++) {
        // Interpolate x values
        x_interpolated[i] = df * i * scale;
        // Interpolate y values
        y_interpolated[i] = arm_linear_interp_f32(&s, x_interpolated[i]);
    }

    // Print interpolated values
    printf("Interpolated Values:\n");
    for (int i = 0; i < nlen; i++) {
        printf("x_interpolated[%d] = %f, y_interpolated[%d] = %f\n", i, x_interpolated[i], i, y_interpolated[i]);
    }

    // Export data if needed
    export_spline(x_in, len, "python/spline_x_in.csv");
    export_spline(y_in, len, "python/spline_y_in.csv");
    export_spline(x_interpolated, nlen, "python/spline_x_out_linear.csv");
    export_spline(y_interpolated, nlen, "python/spline_y_out_linear.csv");
}
