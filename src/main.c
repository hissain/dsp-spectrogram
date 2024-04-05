#include <stdio.h>
#include <stdlib.h>
#include "fft.h"

void generateSomeCompositSignal(){
    int N_SAMPLE = 3002;
    float32_t fs = 25000;
    float32_t fres[] = {10000, 5000, 2500, 580};
    float32_t ampls[] = {1.5, 0.5, 2.5, 0.8};

    float32_t *output = malloc(sizeof(float32_t) * N_SAMPLE);

    generate_composit(fs, fres, ampls, 4, N_SAMPLE, output);
    print_array(output, N_SAMPLE);
}

int main(){
    printf("Hello World from CMSIS DSP  \n");
    //test_ifft();
    //test_cfft();
    generateSpectrogram();
    //generateSomeCompositSignal();
    return 0;
}