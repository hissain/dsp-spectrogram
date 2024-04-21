// Author: Md. Sazzad Hissain Khan
// Copyright (c) 2024 Md. Sazzad Hissain Khan. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "arm_math.h"

#define NOISE_Q 0.500f // Experimental
#define NOISE_R 0.555f // Experimental
#define MEASUREMENT_NOISE 0.09f // Testing 

typedef struct {
    float32_t x_est_last;
    float32_t P_last;
    float32_t Q;
    float32_t R;
} KalmanState;

double frand() {
    return 2 * ((rand() / (double)RAND_MAX) - 0.5);
}

void initializeKalman(KalmanState *kalman) {
    kalman->x_est_last = 0;
    kalman->P_last = 0;
    kalman->Q = NOISE_Q;
    kalman->R = NOISE_R;
}

float32_t predict(KalmanState *kalman) {
    float32_t x_temp_est = kalman->x_est_last;
    float32_t P_temp = kalman->P_last + kalman->Q;
    return x_temp_est;
}

void correct(KalmanState *kalman, float32_t z_measured) {
    float32_t x_temp_est = predict(kalman);
    float32_t P_temp = kalman->P_last + kalman->Q;
    float32_t K = P_temp / (P_temp + kalman->R);
    kalman->x_est_last = x_temp_est + K * (z_measured - x_temp_est);
    kalman->P_last = (1 - K) * P_temp;
}

void printResults(float32_t z_real, float32_t z_measured, float32_t x_est) {
    printf("Ideal    position: %6.3f \n", z_real);
    printf("Measured position: %6.3f [diff:%.3f]\n", z_measured, fabs(z_real - z_measured));
    printf("Kalman   position: %6.3f [diff:%.3f]\n", x_est, fabs(z_real - x_est));
}

int test_kalman_filter(float32_t *signal, int len) {
    KalmanState kalman;
    float32_t z_real = 0.5f; // the ideal value we wish to measure
    float32_t z_measured;
    float32_t sum_error_kalman = 0;
    float32_t sum_error_measure = 0;

    srand(0);
    initializeKalman(&kalman);
    
    for (int i = 0; i < len; i++) {
        z_real = signal[i];
        z_measured = z_real + frand() * MEASUREMENT_NOISE;
        correct(&kalman, z_measured);
        if (i % (len / 10) == 0)
            printResults(z_real, z_measured, kalman.x_est_last);
        
        sum_error_kalman += fabs(z_real - kalman.x_est_last);
        sum_error_measure += fabs(z_real - z_measured);
    }
    
    printf("Total error if using raw measured:  %f\n", sum_error_measure);
    printf("Total error if using kalman filter: %f\n", sum_error_kalman);
    printf("Reduction in error: %d%% \n", 100 - (int)((sum_error_kalman / sum_error_measure) * 100));
    
    return 0;
}


// WITHOUT GROUND TRUTH

#define PROCESS_NOISE 0.1
//#define MEASUREMENT_NOISE 1

float32_t simple_kalman_filter(float32_t *noisy_signal, int len) {
    float32_t filtered_signal[len];
    float32_t x_hat = 0;  // Initial state estimate
    float32_t P = 1;  // Initial state covariance
    float32_t Q = PROCESS_NOISE;  // Process noise covariance
    float32_t R = MEASUREMENT_NOISE;  // Measurement noise covariance

    // Kalman filtering
    for (int t = 0; t < len; t++) {
        // Prediction step
        float32_t x_hat_minus = x_hat;
        float32_t P_minus = P + Q;

        // Update step
        float32_t K = P_minus / (P_minus + R);
        x_hat = x_hat_minus + K * (noisy_signal[t] - x_hat_minus);
        P = (1 - K) * P_minus;

        // Save filtered signal
        filtered_signal[t] = x_hat;
    }
    return 0;
}

int test_kalman_filter_no_ground_truth(float32_t *signal, int len) {
    // Apply simple Kalman filter
    simple_kalman_filter(signal, len);

    return 0;
}

