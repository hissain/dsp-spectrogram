#include <stdio.h>
#include <stdlib.h>

#include "arm_math.h"
#include "spect_utils.h"

#define SIGNAL_LENGTH   1024    // Length of input signal
#define FFT_LENGTH      1024    // Length of FFT
#define NUM_BLOCKS      4     // Number of blocks for Welch method


arm_rfft_fast_instance_f32 fftInstancePsd;

void calculatePSD(float32_t* freqAxis, float32_t* outputPSD){

    float32_t inputSignal[SIGNAL_LENGTH];
    arm_copy_f32(sample_input, inputSignal, SIGNAL_LENGTH);
    //print_array(inputSignal, SIGNAL_LENGTH);

    uint32_t blockSize = SIGNAL_LENGTH / NUM_BLOCKS;
    uint32_t overlapSize = blockSize / 2;

    printf("blockSize = %d\n", blockSize);
    printf("overlapSize = %d\n", overlapSize);

    // Temporary buffers
    float32_t* tempInput = (float32_t*)malloc(FFT_LENGTH * sizeof(float32_t));
    float32_t* tempOutput = (float32_t*)malloc(FFT_LENGTH * sizeof(float32_t));

    // Welch window initialization
    float32_t welchWindow[blockSize];
    for (int i = 0; i < blockSize; i++) {
        welchWindow[i] = 0.53836 - 0.46164 * cos(2 * PI * i / (blockSize - 1));
    }

    // Initialize PSD output
    for (uint32_t i = 0; i < FFT_LENGTH / 2; i++){
        outputPSD[i] = 0.0f;
    }

    // Perform FFT
    arm_rfft_fast_init_f32(&fftInstancePsd, FFT_LENGTH);

    // Loop through blocks
    for (uint32_t i = 0; i < NUM_BLOCKS; i++){

        // Apply Welch window
        arm_fill_f32(0, tempInput, blockSize);
        arm_mult_f32(&inputSignal[i * overlapSize], welchWindow, tempInput, blockSize);

        //arm_fill_f32(0, tempOutput, FFT_LENGTH);
        arm_rfft_fast_f32(&fftInstancePsd, tempInput, tempOutput, 0);

        // Calculate power spectral density (PSD)
        arm_cmplx_mag_squared_f32(tempOutput, tempOutput, FFT_LENGTH / 2);

        // Accumulate PSD
        for (uint32_t j = 0; j < FFT_LENGTH / 2; j++){
            outputPSD[j] += tempOutput[j];
        }
    }

    // Normalize PSD
    for (uint32_t i = 0; i < FFT_LENGTH / 2; i++){
        outputPSD[i] /= NUM_BLOCKS;
    }

    // Generate frequency axis
    for (uint32_t i = 0; i < FFT_LENGTH / 2; i++){
        freqAxis[i] = (float32_t)i / FFT_LENGTH;
    }

    free(tempInput);
    free(tempOutput);
}

int testPsd(){
    
    // Output PSD and frequency axis buffers
    float32_t outputPSD[FFT_LENGTH / 2];
    float32_t freqAxis[FFT_LENGTH / 2];

    // Call function to calculate PSD using Welch method
    calculatePSD(freqAxis, outputPSD);

    // Save PSD data to a file
    FILE *fp;
    fp = fopen("python/psd.txt", "w");
    for (int i = 0; i < FFT_LENGTH / 2; i++){
        fprintf(fp, "%f %f\n", freqAxis[i], outputPSD[i]);
    }
    fclose(fp);
    
    printf("Data saved in python/psd.txt file\n");

    return 0;
}
