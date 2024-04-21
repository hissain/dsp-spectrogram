#include <stdio.h>
#include <stdlib.h>

#include "spect_utils.h"
#include "arm_math.h"

#define NUM_STEPS 100
#define PROCESS_NOISE 0.1
#define MEASUREMENT_NOISE 1

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

    storeSignalIntoFile(filtered_signal, len, "python/kalman.csv");

    return 0;
}

int test_kalman_filter(float32_t *signal, int len) {
    // Apply simple Kalman filter
    simple_kalman_filter(signal, len);

    return 0;
}
