#include "kernel.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

float gaussian(float x, float sigma) {
    return((1.0 / sqrt(2 * PI * pow(sigma, 2))) * pow(Em, (-(pow(x, 2) / (2 * pow(sigma, 2))))));
}

Kernel::Kernel() {
    this->kernelSize = 3;
    this->gaussianBlurStrength = 3;
}

void Kernel::setGaussianKernel(float sigma, int size) {
    this->gaussianBlurStrength = sigma;
    this->kernelSize = size;

    // variable to store the sum of all the values for normalization
    float sum = 0;

    // i = [-size / 2, ... , size / 2]
    int j = -(int)size / 2;
    // j = [-size / 2, ... , size / 2]
    int i = -(int)size / 2;

    free(this->kernel);
    this->kernel = (float*)calloc(size * size, sizeof(float));

    for (int k = 0; k < size * size; k++) {
        // calculate the 2D gaussian values by multiplying the 2 1D values together
        this->kernel[k] = gaussian(i, sigma) * gaussian(j, sigma);
        // calculate the sum
        sum += this->kernel[k];

        // when i reaches the end, increase j and reset i at the beginning
        i++;
        if (i > (int)size / 2) {
            j++;
            i = -(int)size / 2;
        }
    }

    // normalize the kernel by dividing all the values by the sum
    for (int k = 0; k < size * size; k++) {
        this->kernel[k] /= sum;
    }
}

void Kernel::setEdgeDetectionKernel() {
    free(this->kernel);
    this->kernel = (float*)calloc(9, sizeof(float));

    this->kernel[0] = -1;
    this->kernel[1] = -1;
    this->kernel[2] = -1;
    this->kernel[3] = -1;
    this->kernel[4] =  8;
    this->kernel[5] = -1;
    this->kernel[6] = -1;
    this->kernel[7] = -1;
    this->kernel[8] = -1;

    this->kernelSize = 3;
}

void Kernel::setSharpeningKernel() {
    free(this->kernel);
    this->kernel = (float*)calloc(9, sizeof(float));

    this->kernel[0] =  0;
    this->kernel[1] = -1;
    this->kernel[2] =  0;
    this->kernel[3] = -1;
    this->kernel[4] =  5;
    this->kernel[5] = -1;
    this->kernel[6] =  0;
    this->kernel[7] = -1;
    this->kernel[8] =  0;

    this->kernelSize = 3;
}

void Kernel::setBoxBlurKernel(int size) {
    free(this->kernel);
    this->kernel = (float*)calloc(size * size, sizeof(float));

    for (int i = 0; i < size * size; i++) {
        this->kernel[i] = 1.0 / ((float)size * (float)size);
    }

    this->kernelSize = size;
}

void Kernel::setEmbossKernel() {
    free(this->kernel);
    this->kernel = (float*)calloc(9, sizeof(float));

    this->kernel[0] = -2;
    this->kernel[1] = -1;
    this->kernel[2] =  0;
    this->kernel[3] = -1;
    this->kernel[4] =  1;
    this->kernel[5] =  1;
    this->kernel[6] =  0;
    this->kernel[7] =  1;
    this->kernel[8] =  2;

    this->kernelSize = 3;
}

void Kernel::setHorizontalKernel() {
    float kernel[9] = {
        -1, -1, -1,
         2,  2,  2,
        -1, -1, -1
    };
    free(this->kernel);
    this->kernel = (float*)calloc(9, sizeof(float));

    this->kernel[0] = -1;
    this->kernel[1] = -1;
    this->kernel[2] = -1;
    this->kernel[3] =  2;
    this->kernel[4] =  2;
    this->kernel[5] =  2;
    this->kernel[6] = -1;
    this->kernel[7] = -1;
    this->kernel[8] = -1;

    this->kernelSize = 3;
}

void Kernel::setVerticalKernel() {
    free(this->kernel);
    this->kernel = (float*)calloc(9, sizeof(float));

    this->kernel[0] = -1;
    this->kernel[1] =  2;
    this->kernel[2] = -1;
    this->kernel[3] = -1;
    this->kernel[4] =  2;
    this->kernel[5] = -1;
    this->kernel[6] = -1;
    this->kernel[7] =  2;
    this->kernel[8] = -1;

    this->kernelSize = 3;
}

void Kernel::setDiagonalSXKernel() {
    free(this->kernel);
    this->kernel = (float*)calloc(9, sizeof(float));

    this->kernel[0] =  2;
    this->kernel[1] = -1;
    this->kernel[2] = -1;
    this->kernel[3] = -1;
    this->kernel[4] =  2;
    this->kernel[5] = -1;
    this->kernel[6] = -1;
    this->kernel[7] = -1;
    this->kernel[8] =  2;

    this->kernelSize = 3;
}

void Kernel::setDiagonalDXKernel() {
    free(this->kernel);
    this->kernel = (float*)calloc(9, sizeof(float));

    this->kernel[0] = -1;
    this->kernel[1] = -1;
    this->kernel[2] =  2;
    this->kernel[3] = -1;
    this->kernel[4] =  2;
    this->kernel[5] = -1;
    this->kernel[6] =  2;
    this->kernel[7] = -1;
    this->kernel[8] = -1;

    this->kernelSize = 3;
}

void Kernel::setCustomKernel(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
    free(this->kernel);
    this->kernel = (float*)calloc(9, sizeof(float));

    this->kernel[0] = a;
    this->kernel[1] = b;
    this->kernel[2] = c;
    this->kernel[3] = d;
    this->kernel[4] = e;
    this->kernel[5] = f;
    this->kernel[6] = g;
    this->kernel[7] = h;
    this->kernel[8] = i;

    this->kernelSize = 3;
}

float* Kernel::getKernel() {
    return(this->kernel);
}

int Kernel::getKernelSize() {
    return(this->kernelSize);
}

float Kernel::getBlurStrength() {
    return(this->gaussianBlurStrength);
}