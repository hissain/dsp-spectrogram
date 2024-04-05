#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "spect_utils.h"

void print_array(float32_t *data, int size){
    printf("Printing Array:\n");
    for(int i = 0; i < size; i++){
        printf("%f, ", data[i]);
    }
    printf("\n");
}

void generateSomeCompositSignal(){
    int N_SAMPLE = 3002;
    float32_t fs = 25000;
    float32_t fres[] = {10000, 5000, 2500, 580};
    float32_t ampls[] = {1.5, 0.5, 2.5, 0.8};

    float32_t *output = malloc(sizeof(float32_t) * N_SAMPLE);

    generateSomeCompositSignal(fs, fres, ampls, 4, N_SAMPLE, output);
    print_array(output, N_SAMPLE);
}

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

void generateCompositSignal(float32_t fs, float32_t freq[], float32_t ampl[], int freqLen, int n_samples, float32_t *freqOut){
    float dt = 1.0f / fs; // Time step
    float *t = (float*)malloc(n_samples * sizeof(float)); // Time array

    assert(t != NULL);

    // Generate time array
    for (int i = 0; i < n_samples; i++) {
        t[i] = i * dt;
    }

    for (int i = 0; i < n_samples; i++) {
        freqOut[i] = 0;
    }

    for (int f = 0; f < freqLen; f++){
        for (int i = 0; i < n_samples; i++) {
            freqOut[i] += (ampl[f] * sin(2 * M_PI * freq[f] * t[i]));
        }
    }
    free(t);
}


#define SAMPLING_RATE 25000
#define FFT_SIZE 256
#define OVERLAP_FACTOR 0.1

void exportSpectrogramData(float32_t **spectrogram, int binSize, int fftSize, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write spectrogram data to CSV file
    for (int i = 0; i < binSize; i++) {
        // Write time information for each row
        float time = (float)i * (FFT_SIZE * (1 - OVERLAP_FACTOR)) / SAMPLING_RATE; // Calculate time in seconds
        fprintf(fp, "%.6f, ", time);

        for (int j = 0; j < fftSize; j++) {
            fprintf(fp, "%.6f", spectrogram[i][j]);
            if (j != fftSize - 1) {
                fprintf(fp, ", ");
            }
        }
        if (i != binSize - 1) {
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}

