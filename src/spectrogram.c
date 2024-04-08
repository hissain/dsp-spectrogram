#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arm_math_types.h"
#include "transform_functions.h"
#include "support_functions.h"
#include "spect_utils.h"

#define PADDING_SIZE 512  // Choose a suitable padding size

float32_t inputSignal[NUM_SAMPLES + 2 * PADDING_SIZE]; // Add padding to input signal
float32_t fftInput[2 * FFT_SIZE];
float32_t fftOutput[2 * FFT_SIZE];
float32_t magnitude[FFT_SIZE];

SpectrogramOutput *spectrogramData;

arm_rfft_fast_instance_f32 fftInstance;

void allocateSpectrogramSpace(){
    spectrogramData = (SpectrogramOutput *) malloc(sizeof(SpectrogramOutput));
    spectrogramData->fftSize = FFT_SIZE / 2;  // Only first half 
    spectrogramData->binSize = NUM_BINS;
    spectrogramData->Sxx = (float32_t **)malloc(NUM_BINS * sizeof(float32_t *));
    for (int i = 0; i < NUM_BINS; i++){
        spectrogramData->Sxx[i] = (float32_t *)malloc(FFT_SIZE / 2 * sizeof(float32_t));
    }
    spectrogramData->f = (float32_t *)malloc((FFT_SIZE / 2) * sizeof(float32_t));
    for (int i = 0; i < FFT_SIZE / 2; i++) {
        spectrogramData->f[i] = ((i * SAMPLING_RATE) / FFT_SIZE);
    }
    spectrogramData->t = (float32_t *)malloc(NUM_BINS * sizeof(float32_t));
    for (int i = 0; i < NUM_BINS; i++) {
        spectrogramData->t[i] = (float32_t)i * STRIDE / SAMPLING_RATE;
    }
}

void freeSpectrogramSpace(){
    for (int i = 0; i < NUM_BINS; i++){
        free(spectrogramData->Sxx[i]);
    }
    free(spectrogramData->Sxx);
    free(spectrogramData->f);
    free(spectrogramData->t);
    free(spectrogramData);
}

void generateSpectrogram(float32_t *samples, int sample_length) {
    
    // Apply padding to the input signal
    for (int i = 0; i < PADDING_SIZE; i++) {
        inputSignal[i] = 0.0f;
        inputSignal[NUM_SAMPLES + PADDING_SIZE + i] = 0.0f;
    }
    for (int i = 0; i < NUM_SAMPLES; i++) {
        inputSignal[PADDING_SIZE + i] = samples[i];
    }

    arm_rfft_fast_init_f32(&fftInstance, FFT_SIZE);

    exportSignalData(inputSignal + PADDING_SIZE, NUM_SAMPLES, "python/input.csv");

    allocateSpectrogramSpace();

    

    for (int i = 0; i < NUM_BINS; i++) {
        // Copy input signal segment to FFT input buffer with overlapping
        arm_fill_f32(0, fftInput, 2 * FFT_SIZE); // Clear previous data
        arm_copy_f32(&inputSignal[i * STRIDE], fftInput, FFT_SIZE);
        arm_rfft_fast_f32(&fftInstance, fftInput, fftOutput, 0);

        // Calculate magnitude of FFT output
        arm_cmplx_mag_f32(fftOutput, magnitude, FFT_SIZE);

        // Convert magnitude to dB
        for (int j = 0; j < FFT_SIZE; j++) {
            magnitude[j] = 25 * log10f(magnitude[j] + 1e-6); // Add small value to avoid log(0)
        }

        // Store spectrogram data
        arm_copy_f32(magnitude, &spectrogramData->Sxx[i][0], FFT_SIZE);
    }

    // Export spectrogram data
    exportSpectrogramData(spectrogramData, "python/spectrogram.csv");
    freeSpectrogramSpace();
}
