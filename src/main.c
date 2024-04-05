#include <stdio.h>
#include <stdlib.h>
#include "spect_fft.h"

int main(){
    printf("Hello World from CMSIS DSP  \n");
    //test_ifft();
    //test_cfft();
    
    //generateSomeCompositSignal();
    generateSpectrogram();
    
    return 0;
}