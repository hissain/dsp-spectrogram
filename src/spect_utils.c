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

void store_array(float32_t *data, int length, const char *filename) {
    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }
    
    // Write data to the file in CSV format
    for (int i = 0; i < length; i++) {
        fprintf(file, "%.3f", data[i]); // Adjust "%.2f" as per your precision requirement
        if (i < length - 1) {
            fprintf(file, ",");
        } else {
            fprintf(file, "\n");
        }
    }
    
    // Close the file
    fclose(file);
}

void load_array(float32_t *data, int *length, const char *filename) {

    int MAX_LENGTH = 20000;

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Read data from the file
    char line[MAX_LENGTH];
    *length = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");
        while (token != NULL) {
            data[*length] = atof(token); // Convert string to float
            (*length)++;
            if (*length >= MAX_LENGTH) {
                printf("Exceeded maximum length of data array\n");
                fclose(file);
                return;
            }
            token = strtok(NULL, ",");
        }
    }

    // Close the file
    fclose(file);
    printf("Released file: %s\n", filename);
}

void generateSomeCompositSignal(){
    int length = 10000;
    float32_t fs = 48000;
    float32_t freqs[] = {30000, 5000, 12500}; //, 1580, 3000, 21000};
    float32_t ampls[] = {1.5, 6.5, 2.5}; //, 0.8, 5.0, 1.8};

    float32_t *output = malloc(sizeof(float32_t) * length);

    generateCompositSignal(fs, freqs, ampls, 3, length, output);
    //print_array(output, length);
    store_array(output, length, "python/noise.csv");
    printf("Array stored at python/noise.csv\n");
}

void exportSignalData(float32_t *signal, int len, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    printf("Exporting signal data\n");
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
    printf("Generating composite signal\n");
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


void exportSpectrogramData(const SpectrogramOutput *output, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    printf("Exporting spectrogram data\n");
    // Write spectrogram data to CSV file
    for (int i = 0; i < output->binSize; i++) {
        // Write time information for each row
        fprintf(fp, "%.6f, ", output->t[i]);

        for (int j = 0; j < output->fftSize; j++) {
            fprintf(fp, "%.6f", output->Sxx[i][j]);
            if (j != output->fftSize - 1) {
                fprintf(fp, ", ");
            }
        }
        if (i != output->binSize - 1) {
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}


int getHammingWindow(int len, float32_t *window) {
    if (len <= 0 || window == NULL) {
        return -1; // Invalid input parameters
    }

    for (int i = 0; i < len; i++) {
        window[i] = 0.54f - 0.46f * cos(2 * M_PI * i / (len - 1));
    }

    return 0; // Success
}
