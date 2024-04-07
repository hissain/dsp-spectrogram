#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arm_math_types.h"
#include "transform_functions.h"
#include "support_functions.h"
#include "spect_utils.h"

float32_t inputSignal[NUM_SAMPLES];
float32_t fftInput[2 * FFT_SIZE];
float32_t fftOutput[2 * FFT_SIZE];
float32_t magnitude[FFT_SIZE];
float32_t **spectrogram;

arm_rfft_fast_instance_f32 fftInstance;

void allocateSpectrogramSpace(){
    spectrogram = (float32_t **)malloc(NUM_BINS * sizeof(float32_t *));
    for (int i = 0; i < NUM_BINS; i++){
        spectrogram[i] = (float32_t *)malloc(FFT_SIZE / 2 * sizeof(float32_t));
    }
}

void freeSpectrogramSpace(){
    for (int i = 0; i < NUM_BINS; i++){
        free(spectrogram[i]);
    }
    free(spectrogram);
}

float32_t samples[NUM_SAMPLES];
int sample_length;

SpectrogramOutput generateSpectrogram() {
    SpectrogramOutput output;
    output.fftSize = FFT_SIZE / 2;  // Only first half 
    output.binSize = NUM_BINS;
    
    load_array(samples, &sample_length, "python/noise.csv");
    //print_array(samples, sample_length);

    printf("Array loaded, size = %d, processing\n", sample_length);

    arm_copy_f32(&samples[0], inputSignal, NUM_SAMPLES);
    arm_rfft_fast_init_f32(&fftInstance, FFT_SIZE);

    exportSignalData(inputSignal, NUM_SAMPLES, "python/input.csv");

    allocateSpectrogramSpace();

    int stepSize = FFT_SIZE * (1 - OVERLAP_FACTOR); // Calculate the step size for overlapping

    // Allocate memory for time (t) array
    output.t = (float32_t *)malloc(NUM_BINS * sizeof(float32_t));
    for (int i = 0; i < NUM_BINS; i++) {
        output.t[i] = (float32_t)i * stepSize / SAMPLING_RATE;
    }

    // Allocate memory for frequency (f) array
    output.f = (float32_t *)malloc((FFT_SIZE / 2) * sizeof(float32_t));
    for (int i = 0; i < FFT_SIZE / 2; i++) {
        output.f[i] = ((float32_t)i * SAMPLING_RATE) / FFT_SIZE;
    }

    for (int i = 0; i < NUM_BINS; i++) {
        // Copy input signal segment to FFT input buffer with overlapping
        arm_fill_f32(0, fftInput, 2 * FFT_SIZE); // Clear previous data
        arm_copy_f32(&inputSignal[i * stepSize], fftInput, FFT_SIZE);
        arm_rfft_fast_f32(&fftInstance, fftInput, fftOutput, 0);

        // Calculate magnitude of FFT output
        arm_cmplx_mag_f32(fftOutput, magnitude, FFT_SIZE);

        // Convert magnitude to dB
        for (int j = 0; j < FFT_SIZE; j++) {
            magnitude[j] = 25 * log10f(magnitude[j] + 1e-6); // Add small value to avoid log(0)
        }

        // Store spectrogram data
        arm_copy_f32(magnitude, &spectrogram[i][0], FFT_SIZE);
    }

    output.Sxx = spectrogram;

    exportSpectrogramData(&output, "python/spec1.csv");

    freeSpectrogramSpace();

    return output;
}
