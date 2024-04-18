#include <stdio.h>
#include <stdlib.h>

#include "spect_utils.h"
#include "dsp.h"

void spline_cubic_interpolation(float32_t *x_in, float32_t *y_in, int len_in, float32_t *x_out, float32_t *y_out, int *len_out){

}


void export_spline(float32_t *data, int len){
    // Save PSD data to a file
    FILE *fp;
    fp = fopen("python/spline.csv", "w");
    if (fp != NULL) {
        for (int i = 0; i < len; i++){
            fprintf(fp, "%f \n", data[i]);
        }
        fclose(fp);
    } else {
        printf("Error opening file for writing\n");
    }
}

void test_spline_cubic_interpolation(){

    float32_t x_in[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float32_t y_in[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    float32_t x_out[20] = {1, 1.3, 2, 2.7, 3, -3.5, -4, 2.5, 5, 5.5, 6.5, -6.5, -7, 7.5, 8, 9.5, 9, -9.5, -10, 10.5};
    float32_t y_out[20] = {0,};

    float32_t coef[30];
    float32_t buff[20];

    float32_t *x_in_p = &x_in[0];
    float32_t *y_in_p = &y_in[0];
    float32_t *x_out_p = &x_out[0];
    float32_t *y_out_p = &y_out[0];
    float32_t *cp = &coef[0];
    float32_t *bp = &buff[0];

    arm_spline_instance_f32 S;
    arm_spline_init_f32(&S, ARM_SPLINE_PARABOLIC_RUNOUT, x_in_p, y_in_p, 10, cp, bp);
    arm_spline_f32(&S, x_out_p, y_out_p, 20);

    print_array(x_out, 20);
    print_array(y_out, 20);

    export_spline(y_out, 20);
}