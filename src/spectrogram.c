#include <stdio.h>
#include "arm_math_types.h"
#include "dsp/transform_functions.h"
#include "dsp/support_functions.h"
#include "arm_const_structs.h"


#define FFT_SIZE 1024
#define NUM_SAMPLES 2048
#define LOG2_FFT_SIZE 10

float32_t inputSignal[NUM_SAMPLES];
float32_t fftInput[2 * FFT_SIZE];
float32_t fftOutput[2 * FFT_SIZE];
float32_t magnitude[FFT_SIZE];
float32_t spectrogram[NUM_SAMPLES / FFT_SIZE][FFT_SIZE];

arm_rfft_fast_instance_f32 fftInstance;

void generateSpectrogram() {


    arm_rfft_fast_init_f32(&fftInstance, FFT_SIZE);
   

    for (int i = 0; i < NUM_SAMPLES / FFT_SIZE; i++) {
        
         // Copy input signal segment to FFT input buffer

        arm_fill_f32(0, fftInput, 2 * FFT_SIZE); // Clear previous data
        arm_copy_f32(&inputSignal[i * FFT_SIZE], fftInput, FFT_SIZE);

        arm_rfft_fast_f32(&fftInstance, fftInput, fftOutput, 0);

        // Calculate magnitude of FFT output
        arm_cmplx_mag_f32(fftOutput, magnitude, FFT_SIZE);

        // Convert magnitude to dB
        for (int j = 0; j < FFT_SIZE; j++) {
            magnitude[j] = 20 * log10f(magnitude[j] + 1e-6); // Add small value to avoid log(0)
        }

        // Store spectrogram data
        arm_copy_f32(magnitude, &spectrogram[i][0], FFT_SIZE);
    }

    for (int i = 0; i < NUM_SAMPLES / FFT_SIZE; i++){
        for (int j = 0; j < FFT_SIZE; j++){
            printf("%.3f, ", spectrogram[i][j]);
        }
        printf("\n");
    }
}
