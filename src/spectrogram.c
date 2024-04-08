#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arm_math_types.h"
#include "transform_functions.h"
#include "support_functions.h"
#include "spect_utils.h"

void generateSpectrogram(float32_t *samples, int sample_length, int padding_size, int sampling_rate, int fft_size, float overlap_factor) {
    printf("Generating spectrogram...\n");

    // Print important parameters
    printf("Parameters:\n");
    printf("Sample Length: %d\n", sample_length);
    printf("Padding Size: %d\n", padding_size);
    printf("Sampling Rate: %d\n", sampling_rate);
    printf("FFT Size: %d\n", fft_size);
    printf("Overlap Factor: %.2f\n", overlap_factor);

    // Add padding to the input signal
    float32_t inputSignal[sample_length + 2 * padding_size];
    printf("Padding input signal...\n");
    for (int i = 0; i < padding_size; i++) {
        inputSignal[i] = 0.0f;
        inputSignal[sample_length + padding_size + i] = 0.0f;
    }
    for (int i = 0; i < sample_length; i++) {
        inputSignal[padding_size + i] = samples[i];
    }

    // Initialize FFT instance
    printf("Initializing FFT instance...\n");
    arm_rfft_fast_instance_f32 fftInstance;
    arm_rfft_fast_init_f32(&fftInstance, fft_size);

    // Allocate space for spectrogram data
    printf("Allocating space for spectrogram data...\n");
    SpectrogramOutput *spectrogramData = (SpectrogramOutput *) malloc(sizeof(SpectrogramOutput));
    spectrogramData->freqSize = fft_size / 2;  // Only first half
    spectrogramData->binSize = ceil((float)(sample_length - fft_size) / (fft_size * (1 - overlap_factor))) + 1;
    spectrogramData->Sxx = (float32_t **)malloc(spectrogramData->binSize * sizeof(float32_t *));
    for (int i = 0; i < spectrogramData->binSize; i++){
        spectrogramData->Sxx[i] = (float32_t *)malloc(spectrogramData->freqSize * sizeof(float32_t));
    }
    spectrogramData->f = (float32_t *)malloc(spectrogramData->freqSize * sizeof(float32_t));
    for (int i = 0; i < spectrogramData->freqSize; i++) {
        spectrogramData->f[i] = ((i * sampling_rate) / fft_size);
    }
    spectrogramData->t = (float32_t *)malloc(spectrogramData->binSize * sizeof(float32_t));
    for (int i = 0; i < spectrogramData->binSize; i++) {
        spectrogramData->t[i] = (float32_t)i * (fft_size * (1 - overlap_factor)) / sampling_rate;
    }

    // Generate spectrogram
    printf("Generating spectrogram data...\n");
    float32_t fftInput[fft_size];
    float32_t fftOutput[fft_size];
    float32_t magnitude[fft_size];
    for (int i = 0; i < spectrogramData->binSize; i++) {
        // Print current iteration and related information
        printf("Iteration %03d/%d: segment: %.3f - %.3f seconds\n", i + 1, spectrogramData->binSize, 
            spectrogramData->t[i], spectrogramData->t[i] + (1.0f * fft_size / sampling_rate));

        // Check if the remaining portion of signals is less than the block size
        int blockSize = fft_size;
        int overlapSize = fft_size * overlap_factor;
        if ((sample_length - (i * overlapSize)) < blockSize) {
            // If less, pad the remaining portion with zeros
            printf("Padding remaining portion with zeros...\n");
            arm_fill_f32(0, fftInput, blockSize);
            arm_copy_f32(&inputSignal[i * overlapSize], fftInput, sample_length - (i * overlapSize));
        } else {
            // Otherwise, copy the block of signals
            arm_copy_f32(&inputSignal[i * overlapSize], fftInput, blockSize);
        }
        // Perform FFT
        arm_rfft_fast_f32(&fftInstance, fftInput, fftOutput, 0);

        // Calculate magnitude of FFT output
        arm_cmplx_mag_f32(fftOutput, magnitude, fft_size / 2);

        // Convert magnitude to dB if needed
        for (int j = 0; j < fft_size; j++) {
            magnitude[j] = 25 * log10f(magnitude[j] + 1e-6); // Add small value to avoid log(0)
        }

        // Store spectrogram data
        arm_copy_f32(magnitude, &spectrogramData->Sxx[i][0], fft_size / 2);
    }

    // Export spectrogram data
    printf("Exporting spectrogram data...\n");
    exportSpectrogramData(spectrogramData, "python/spectrogram.csv");

    // Free allocated space
    printf("Freeing allocated space...\n");
    for (int i = 0; i < spectrogramData->binSize; i++){
        free(spectrogramData->Sxx[i]);
    }
    free(spectrogramData->Sxx);
    free(spectrogramData->f);
    free(spectrogramData->t);
    free(spectrogramData);

    printf("Spectrogram generation complete.\n");
}


