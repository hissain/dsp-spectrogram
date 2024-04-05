#include <stdio.h>
#include "fft.h"
#include "arm_math_types.h"
#include "transform_functions.h"
#include "support_functions.h"
#include "arm_const_structs.h"


//#define FFT_SIZE 1024
//#define NUM_SAMPLES 2048
#define NUM_SAMPLES 3002
#define FFT_SIZE 256
#define LOG2_FFT_SIZE 10
#define NUM_BINS ((NUM_SAMPLES + FFT_SIZE - 1) / FFT_SIZE)

float32_t inputSignal[NUM_SAMPLES];
float32_t fftInput[2 * FFT_SIZE];
float32_t fftOutput[2 * FFT_SIZE];
float32_t magnitude[FFT_SIZE];
float32_t spectrogram[NUM_BINS][FFT_SIZE];

arm_rfft_fast_instance_f32 fftInstance;

void exportSignalData(float32_t *signal, int len, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write spectrogram data to CSV file
    for (int i = 0; i < len; i++) {
        if (i != len-1){
            fprintf(fp, "%f, ", signal[i]);
        }else{
            fprintf(fp, "%f\n", signal[i]);
        }
    }
    fclose(fp);
}

void exportSpectrogramData(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write spectrogram data to CSV file
    for (int i = 0; i < NUM_BINS; i++) {
        for (int j = 0; j < FFT_SIZE; j++) {
			if (j != FFT_SIZE - 1){
				fprintf(fp, "%.6f, ", spectrogram[i][j]);
			}else{
				fprintf(fp, "%.6f", spectrogram[i][j]);
			}
        }
		if(i != NUM_BINS - 1){
			fprintf(fp, "\n");
		}
    }
    fclose(fp);
}

void generateSpectrogram() {


    arm_copy_f32(&sample_input[0], inputSignal, NUM_SAMPLES);
    arm_rfft_fast_init_f32(&fftInstance, FFT_SIZE);
    
    exportSignalData(inputSignal, NUM_SAMPLES, "python/input.csv");
    //print_array(fftInput, FFT_SIZE);
    for (int i = 0; i < NUM_BINS; i++) {
        
         // Copy input signal segment to FFT input buffer

        arm_fill_f32(0, fftInput, 2 * FFT_SIZE); // Clear previous data
        arm_copy_f32(&inputSignal[i * FFT_SIZE], fftInput, FFT_SIZE);

        printf("Contents of %dth input\n", i);
        print_array(fftInput, FFT_SIZE);

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

    for (int i = 0; i < NUM_BINS; i++){
        for (int j = 0; j < FFT_SIZE; j++){
            printf("%.3f, ", spectrogram[i][j]);
        }
        printf("\n");
    }

    printf("Exporting spectrogram data\n");
    exportSpectrogramData("python/spec1.csv");
}
