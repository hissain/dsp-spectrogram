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

void test_spline_cubic_interpolation(float32_t x[], int len, int nlen){

    float32_t x_in[len];
    float32_t y_in[len];

    float32_t df = 1/48000.0f;
    float32_t scale = (1.0f * nlen) / len;

    for(int i = 0; i < len; i++){
        x_in[i] = df*i;
        y_in[i] = x[i];
    }

    float32_t x_out[nlen];
    float32_t y_out[nlen];

    float32_t df_n = (x_in[len - 1] - x_in[0]) / nlen; 

    for(int i = 0; i < nlen; i++){
        x_out[i] = df_n*i;
    }

    printf("df: %lf\n", df);
    printf("df_n: %lf\n", df_n);
    printf("nlen: %d\n", nlen);


    float32_t coef[3*len];
    float32_t buff[2*len];

    float32_t *x_in_p = &x_in[0];
    float32_t *y_in_p = &y_in[0];
    float32_t *x_out_p = &x_out[0];
    float32_t *y_out_p = &y_out[0];
    float32_t *cp = &coef[0];
    float32_t *bp = &buff[0];


    arm_spline_instance_f32 S;
    arm_spline_init_f32(&S, ARM_SPLINE_PARABOLIC_RUNOUT, x_in_p, y_in_p, len, cp, bp);
    arm_spline_f32(&S, x_out_p, y_out_p, nlen);

    print_array(x_out, nlen);
    print_array(y_out, nlen);

    export_spline(x_in, len, "python/spline_x_in.csv");
    export_spline(y_in, len, "python/spline_y_in.csv");
    export_spline(x_out, nlen, "python/spline_x_out.csv");
    export_spline(y_out, nlen, "python/spline_y_out.csv");
}