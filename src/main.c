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

    generateSomeCompositSignal(samples, length);
    storeSignalIntoFile(samples, length, "python/noise.csv");
    generateSpectrogram(samples, length);
    generatePowerSpectralDensity();

    return 0;
}