#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "spect_fft.h"
#include "spect_utils.h"

int main(){
    printf("Hello World from CMSIS DSP  \n");
    //test_ifft();
    //test_cfft();
    
    generateSomeCompositSignal();
    generateSpectrogram();
    generatePowerSpectralDensity();

    return 0;
}