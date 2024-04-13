// Author: Md. Sazzad Hissain Khan
// Copyright (c) 2024 Md. Sazzad Hissain Khan. All rights reserved.

#include <stdio.h>
#include <math.h>
#include "arm_const_structs.h"
#include "arm_math.h"
#include "spect_utils.h"

// Define the custom instance of the FFT function
static arm_cfft_instance_f32 custom_fft_inst;

void exportHilbertTransformedOutput(float32_t* complexOutput, int length) {
    // Save PSD data to a file
    FILE *fp;
    fp = fopen("python/hilbert_output.csv", "w");
    if (fp != NULL) {
        for (int i = 0; i < length; i++){
            fprintf(fp, "%f\n", complexOutput[i]);
        }
        fclose(fp);
        printf("Hilbert output saved in python/hilbert_output.csv file\n");
    } else {
        printf("Error opening file for writing\n");
    }
}

int hilbertTransform(float32_t* inputSignal, int length) {
    // Initialize CMSIS DSP library complex arrays
    float32_t complexInput[length];
    float32_t complexOutput[length];

    // Initialize custom instance of the FFT function with the desired length
    arm_cfft_init_f32(&custom_fft_inst, length);
    arm_copy_f32(inputSignal, (float32_t *)complexInput, length); // Copy real part

    // Perform Fourier transform using the custom instance
    arm_cfft_f32(&custom_fft_inst, complexInput, 0, 1); // Perform FFT

    // Apply Hilbert transform
    // Since the input signal is real, we only need to keep the positive frequency components
    for (int i = 2; i < length; i += 2){
        complexInput[i] *= 2; // Multiply by 2 to account for the positive and negative frequencies
        complexInput[i + 1] *= 2;
    }

    // Inverse Fourier transform
    arm_cfft_f32(&custom_fft_inst, complexInput, 1, 1); // Perform IFFT

    // Extract imaginary part (Hilbert transform)
    arm_copy_f32(complexInput, (float32_t *)complexOutput, length);

    /*for (int i = 0; i < length; i += 2){
        complexOutput[i] = complexInput[i];
        //complexOutput[i + 1] = 0.0f;
    }*/

    // Export Hilbert transformed output
    exportHilbertTransformedOutput(complexOutput, length);

    return 0;
}
