#include <stdio.h>
#include <stdlib.h>
#include "arm_math_types.h"
#include "transform_functions.h"
#include "support_functions.h"
#include "spect_utils.h"

#define SAMPLING_RATE 25000
#define NUM_SAMPLES 3002
#define FFT_SIZE 256
#define LOG2_FFT_SIZE 10
#define OVERLAP_FACTOR 0.1

//#define NUM_BINS (NUM_SAMPLES / FFT_SIZE )
//#define NUM_BINS ((NUM_SAMPLES + FFT_SIZE - 1) / FFT_SIZE)
#define NUM_BINS (ceil((float)(NUM_SAMPLES - FFT_SIZE) / (FFT_SIZE * (1 - OVERLAP_FACTOR))) + 1)

float32_t inputSignal[NUM_SAMPLES];
float32_t fftInput[2 * FFT_SIZE];
float32_t fftOutput[2 * FFT_SIZE];
float32_t magnitude[FFT_SIZE];
float32_t **spectrogram;

arm_rfft_fast_instance_f32 fftInstance;

void allocateSpectrogramSpace(){
    // Allocate memory for the spectrogram array
    spectrogram = (float32_t **)malloc(NUM_BINS * sizeof(float32_t *));
    for (int i = 0; i < NUM_BINS; i++){
        spectrogram[i] = (float32_t *)malloc(FFT_SIZE * sizeof(float32_t));
    }
}

void freeSpectrogramSpace(){
    // Free memory allocated for the spectrogram array
    for (int i = 0; i < NUM_BINS; i++){
        free(spectrogram[i]);
    }
    free(spectrogram);
}

void generateSpectrogram() {
    printf("Generating spectrogram data\n");
    arm_copy_f32(&sample_input[0], inputSignal, NUM_SAMPLES);
    arm_rfft_fast_init_f32(&fftInstance, FFT_SIZE);
    
    exportSignalData(inputSignal, NUM_SAMPLES, "python/input.csv");
    allocateSpectrogramSpace();

    int stepSize = FFT_SIZE * (1 - OVERLAP_FACTOR); // Calculate the step size for overlapping

    for (int i = 0; i < NUM_BINS; i++) {
        // Copy input signal segment to FFT input buffer with overlapping
        arm_fill_f32(0, fftInput, 2 * FFT_SIZE); // Clear previous data
        arm_copy_f32(&inputSignal[i * stepSize], fftInput, FFT_SIZE);
        arm_rfft_fast_f32(&fftInstance, fftInput, fftOutput, 0);

        // Calculate magnitude of FFT output
        arm_cmplx_mag_f32(fftOutput, magnitude, FFT_SIZE);

        // Convert magnitude to dB
        for (int j = 0; j < FFT_SIZE; j++) {
            magnitude[j] = 10 * log10f(magnitude[j] + 1e-6); // Add small value to avoid log(0)
        }

        // Store spectrogram data
        arm_copy_f32(magnitude, &spectrogram[i][0], FFT_SIZE);
    }

    printf("Exporting spectrogram data\n");
    exportSpectrogramData(spectrogram, NUM_BINS, FFT_SIZE, "python/spec1.csv");
    freeSpectrogramSpace();
}

