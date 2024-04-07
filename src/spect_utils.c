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

void storeSignalIntoFile(float32_t *data, int length, const char *filename) {
    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }
    
    // Write data to the file in CSV format
    for (int i = 0; i < length; i++) {
        if (i < length - 1) {
            fprintf(file, "%.3f\n", data[i]);
        } else {
            fprintf(file, "%.3f", data[i]);
        }
    }
    
    // Close the file
    fclose(file);
}

void loadSignalFromFile(float32_t *data, int *length, const char *filename) {
    int MAX_LINE_LENGTH = NUM_SAMPLES + 1; // +1 for newline safety 
    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Read data from the file
    char line[MAX_LINE_LENGTH];
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");

        // Loop through tokens separated by commas
        while (token != NULL) {
            // Convert string to float and store in the data array
            data[i++] = atof(token);
            if (i >= MAX_LINE_LENGTH) {
                printf("Exceeded maximum length of line\n");
                fclose(file);
                return;
            }
            // Get the next token
            token = strtok(NULL, ",");
        }
    }
    *length = i;

    fclose(file);
}

void generateSomeCompositSignal(){
    int length = 102400;
    float32_t fs = 48000;
    float32_t freqs[] = {14000, 5000, 10000};//, 1580, 3000, 21000};
    float32_t ampls[] = {3.5, 2.5, 2.5};//, 0.8, 5.0, 1.8};

    float32_t *output = malloc(sizeof(float32_t) * length);

    generateCompositSignal(fs, freqs, ampls, 3, length, output);
    //print_array(output, length);
    storeSignalIntoFile(output, length, "python/noise.csv");
    printf("Composit signal generated and stored at python/noise.csv, size:%d\n", length);
    free(output);
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
        fprintf(fp, "%f\n", signal[i]);
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
        window[i] = 0.53836f - 0.46164f * cos(2 * M_PI * i / (len - 1));
    }
    return 0; // Success
}

