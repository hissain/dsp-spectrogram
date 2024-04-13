// Author: Md. Sazzad Hissain Khan
// Copyright (c) 2024 Md. Sazzad Hissain Khan. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "arm_math.h"
#include "spect_utils.h"

#define PSD_FS 48000
#define PSD_NUM_SAMPLES   102400            // Length of input signal
#define PSD_FFT_LENGTH      1024            // Length of FFT
#define PSD_BLOCK_LENGTH    PSD_FFT_LENGTH  // Number points in each block
#define PSD_OVERLAP_FACTOR  0.5f
#define PSD_NUM_BLOCKS (int)(ceil((float)(PSD_NUM_SAMPLES - PSD_FFT_LENGTH) / (PSD_FFT_LENGTH * (1 - PSD_OVERLAP_FACTOR))) + 1)

arm_rfft_fast_instance_f32 fftInstancePsd;

// Output PSD and frequency axis buffers
float32_t outputPSD_dB[PSD_FFT_LENGTH / 2];
float32_t freqAxis[PSD_FFT_LENGTH / 2];

void exportPowerSpectralDensity(){
    // Save PSD data to a file
    FILE *fp;
    fp = fopen("python/psd.csv", "w");
    if (fp != NULL) {
        for (int i = 0; i < PSD_FFT_LENGTH / 2; i++){
            fprintf(fp, "%f %f\n", freqAxis[i], outputPSD_dB[i]);
        }
        fclose(fp);
        printf("Data saved in python/psd.csv file\n");
    } else {
        printf("Error opening file for writing\n");
    }
}

void generatePowerSpectralDensity(float32_t* samples, int sample_length){

    uint32_t blockSize = PSD_FFT_LENGTH;
    uint32_t overlapSize = PSD_BLOCK_LENGTH * PSD_OVERLAP_FACTOR;

    printf("NUM_SAMPLES = %d\n", PSD_NUM_SAMPLES);
    printf("BLOCK_LENGTH = %d\n", PSD_BLOCK_LENGTH);
    printf("NUM_BLOCKS = %d\n", PSD_NUM_BLOCKS);
    printf("blockSize = %d\n", blockSize);
    printf("overlapSize = %d\n", overlapSize);

    // Temporary buffers
    float32_t tempInput[PSD_FFT_LENGTH];
    float32_t tempOutput[PSD_FFT_LENGTH];

    // Welch window initialization
    float32_t welchWindow[blockSize];
    getHammingWindow(blockSize, &welchWindow[0]);

    // Initialize PSD output
    for (uint32_t i = 0; i < PSD_FFT_LENGTH / 2; i++){
        outputPSD_dB[i] = 0.0f;
    }

    // Perform FFT
    arm_rfft_fast_init_f32(&fftInstancePsd, blockSize);

    // Loop through blocks
    for (uint32_t i = 0; i < PSD_NUM_BLOCKS; i++){

        // Check if the remaining portion of signals is less than the block size
        if ((PSD_NUM_SAMPLES - (i * overlapSize)) < blockSize) {
            // If less, pad the remaining portion with zeros
            arm_fill_f32(0, tempInput, blockSize);
            arm_copy_f32(&samples[i * overlapSize], tempInput, PSD_NUM_SAMPLES - (i * overlapSize));
        } else {
            // Otherwise, copy the block of signals
            arm_copy_f32(&samples[i * overlapSize], tempInput, blockSize);
        }

        arm_mult_f32(tempInput, welchWindow, tempInput, blockSize);
        
        arm_fill_f32(0, tempOutput, PSD_FFT_LENGTH);
        arm_rfft_fast_f32(&fftInstancePsd, tempInput, tempOutput, 0);

        // Calculate power spectral density (PSD)
        arm_cmplx_mag_squared_f32(tempOutput, tempOutput, PSD_FFT_LENGTH / 2);
        
        // Accumulate PSD in dB
        for (uint32_t j = 0; j < PSD_FFT_LENGTH / 2; j++){
            outputPSD_dB[j] += 10 * log10(tempOutput[j] + 1e-6); // Add small value to avoid log(0)
        }
    }

    // Normalize PSD
    for (uint32_t i = 0; i < PSD_FFT_LENGTH / 2; i++){
        outputPSD_dB[i] /= PSD_NUM_BLOCKS;
    }

    // Generate frequency axis
    for (uint32_t i = 0; i < PSD_FFT_LENGTH / 2; i++){
        freqAxis[i] = (float32_t)i * (PSD_FS / PSD_FFT_LENGTH);
    }

    exportPowerSpectralDensity();
}
