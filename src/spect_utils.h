#ifndef SPECT_UTILS_H
#define SPECT_UTILS_H

#include "arm_math_types.h"

#define FILE_NAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define DEBUG_PRINT printf("Debugging: File %s, Line %d\n", FILE_NAME, __LINE__);

#define SAMPLING_RATE 48000
#define FFT_SIZE 1024
#define OVERLAP_FACTOR 0.5
#define NUM_SAMPLES 102400
#define NUM_BINS (ceil((float)(NUM_SAMPLES - FFT_SIZE) / (FFT_SIZE * (1 - OVERLAP_FACTOR))) + 1)
#define STRIDE  ((int)(FFT_SIZE * (1 - OVERLAP_FACTOR)))

typedef struct {
    int fftSize;
    int binSize;
    float32_t **Sxx;
    float32_t *t;
    float32_t *f;
} SpectrogramOutput;

void print_array(float32_t *data, int size);
void storeSignalIntoFile(float32_t *data, int length, const char *filename);
void loadSignalFromFile(float32_t *data, int *length, const char *filename);

void generateSomeCompositSignal(float32_t *samples, int length);
void generateCompositSignal(float32_t fs, float32_t freq[], float32_t ampl[], int freqLen, int n_samples, float32_t *freqOut);
void generateSpectrogram(float32_t *samples, int sample_length);

void exportSignalData(float32_t *signal, int len, char *filename);
void exportSpectrogramData(const SpectrogramOutput *spectrogramData, const char *filename);
int getHammingWindow(int len, float32_t *window);


void generatePowerSpectralDensity();

#endif