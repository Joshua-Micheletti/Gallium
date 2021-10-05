#include "kernel.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

float gaussian(float x, float sigma) {
    return((1.0 / sqrt(2 * PI * pow(sigma, 2))) * pow(Em, (-(pow(x, 2) / (2 * pow(sigma, 2))))));
}

Kernel::Kernel() {

}

float* Kernel::getGaussianKernel(float sigma, int size) {
    // variable to store the sum of all the values for normalization
    float sum = 0;

    // i = [-size / 2, ... , size / 2]
    int j = -(int)size / 2;
    // j = [-size / 2, ... , size / 2]
    int i = -(int)size / 2;

    float* kernel = (float*)calloc(size * size, sizeof(float));

    for (int k = 0; k < size * size; k++) {
        // calculate the 2D gaussian values by multiplying the 2 1D values together
        kernel[k] = gaussian(i, sigma) * gaussian(j, sigma);
        // calculate the sum
        sum += kernel[k];

        // when i reaches the end, increase j and reset i at the beginning
        i++;
        if (i > (int)size / 2) {
            j++;
            i = -(int)size / 2;
        }
    }

    // normalize the kernel by dividing all the values by the sum
    for (int k = 0; k < size * size; k++) {
        kernel[k] /= sum;
    }

    return(kernel);
}

float* Kernel::getEdgeDetectionKernel() {
    float kernel[9] = {
        -1, -1, -1,
        -1,  8, -1,
        -1, -1, -1
    };

    return(kernel);
}

float* Kernel::getSharpeningKernel() {
    float kernel[9] = {
         0, -1,  0,
        -1,  5, -1,
         0, -1,  0
    };

    return(kernel);
}

float* Kernel::getBoxBlurKernel(int size) {
    float* kernel = (float*)calloc(size * size, sizeof(float));

    for (int i = 0; i < size * size; i++) {
        kernel[i] = 1.0 / ((float)size * (float)size);
    }

    return(kernel);
}