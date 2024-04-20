// Author: Md. Sazzad Hissain Khan
// Copyright (c) 2024 Md. Sazzad Hissain Khan. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "spect_fft.h"
#include "spect_utils.h"
#include "dsp.h"

int main(){
    printf("Hello World from CMSIS DSP  \n");
    //test_ifft();
    //test_cfft();
    
    float32_t samples[NUM_SAMPLES];
    int length = NUM_SAMPLES;

    generateCompositSignalWithLength(samples, length);
    //generateSpectrogram(samples, length, 0, 48000, 1024, 0.5);
    //generatePowerSpectralDensity(samples, length);
    //hilbertTransform(samples, length);

    test_spline_cubic_interpolation(samples, 250, 100, 48000.0f);

    return 0;
}