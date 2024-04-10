#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "spect_fft.h"
#include "spect_utils.h"

int main(){
    printf("Hello World from CMSIS DSP  \n");
    //test_ifft();
    //test_cfft();
    
    float32_t samples[NUM_SAMPLES];
    int length = NUM_SAMPLES;

    generateCompositSignalWithLength(samples, length);
    generateSpectrogram(samples, length, 0, 48000, 1024, 0.5);
    generatePowerSpectralDensity(samples, length);
    hilbertTransform(samples, length);

    return 0;
}