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