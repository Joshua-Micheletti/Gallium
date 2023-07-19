#include "Kernel.h"

float gaussian(float x, float sigma) {
    return((1.0 / sqrt(2 * PI * pow(sigma, 2))) * pow(Em, (-(pow(x, 2) / (2 * pow(sigma, 2))))));
}

Kernel::Kernel() {
    this->m_kernelSize = 3;
    this->m_gaussianBlurStrength = 3;
}

void Kernel::setGaussianKernel(float sigma, int size) {
    this->m_gaussianBlurStrength = sigma;
    this->m_kernelSize = size;

    // variable to store the sum of all the values for normalization
    float sum = 0;

    // i = [-size / 2, ... , size / 2]
    int j = -(int)size / 2;
    // j = [-size / 2, ... , size / 2]
    int i = -(int)size / 2;

    free(this->m_kernel);
    this->m_kernel = (float*)calloc(size * size, sizeof(float));

    for (int k = 0; k < size * size; k++) {
        // calculate the 2D gaussian values by multiplying the 2 1D values together
        this->m_kernel[k] = gaussian(i, sigma) * gaussian(j, sigma);
        // calculate the sum
        sum += this->m_kernel[k];

        // when i reaches the end, increase j and reset i at the beginning
        i++;
        if (i > (int)size / 2) {
            j++;
            i = -(int)size / 2;
        }
    }

    // normalize the m_kernel by dividing all the values by the sum
    for (int k = 0; k < size * size; k++) {
        this->m_kernel[k] /= sum;
    }
}

void Kernel::setEdgeDetectionKernel() {
    free(this->m_kernel);
    this->m_kernel = (float*)calloc(9, sizeof(float));

    this->m_kernel[0] = -1;
    this->m_kernel[1] = -1;
    this->m_kernel[2] = -1;
    this->m_kernel[3] = -1;
    this->m_kernel[4] =  8;
    this->m_kernel[5] = -1;
    this->m_kernel[6] = -1;
    this->m_kernel[7] = -1;
    this->m_kernel[8] = -1;

    this->m_kernelSize = 3;
}

void Kernel::setSharpeningKernel() {
    free(this->m_kernel);
    this->m_kernel = (float*)calloc(9, sizeof(float));

    this->m_kernel[0] =  0;
    this->m_kernel[1] = -1;
    this->m_kernel[2] =  0;
    this->m_kernel[3] = -1;
    this->m_kernel[4] =  5;
    this->m_kernel[5] = -1;
    this->m_kernel[6] =  0;
    this->m_kernel[7] = -1;
    this->m_kernel[8] =  0;

    this->m_kernelSize = 3;
}

void Kernel::setBoxBlurKernel(int size) {
    free(this->m_kernel);
    this->m_kernel = (float*)calloc(size * size, sizeof(float));

    for (int i = 0; i < size * size; i++) {
        this->m_kernel[i] = 1.0 / ((float)size * (float)size);
    }

    this->m_kernelSize = size;
}

void Kernel::setEmbossKernel() {
    free(this->m_kernel);
    this->m_kernel = (float*)calloc(9, sizeof(float));

    this->m_kernel[0] = -2;
    this->m_kernel[1] = -1;
    this->m_kernel[2] =  0;
    this->m_kernel[3] = -1;
    this->m_kernel[4] =  1;
    this->m_kernel[5] =  1;
    this->m_kernel[6] =  0;
    this->m_kernel[7] =  1;
    this->m_kernel[8] =  2;

    this->m_kernelSize = 3;
}

void Kernel::setHorizontalKernel() {
    float m_kernel[9] = {
        -1, -1, -1,
         2,  2,  2,
        -1, -1, -1
    };
    free(this->m_kernel);
    this->m_kernel = (float*)calloc(9, sizeof(float));

    this->m_kernel[0] = -1;
    this->m_kernel[1] = -1;
    this->m_kernel[2] = -1;
    this->m_kernel[3] =  2;
    this->m_kernel[4] =  2;
    this->m_kernel[5] =  2;
    this->m_kernel[6] = -1;
    this->m_kernel[7] = -1;
    this->m_kernel[8] = -1;

    this->m_kernelSize = 3;
}

void Kernel::setVerticalKernel() {
    free(this->m_kernel);
    this->m_kernel = (float*)calloc(9, sizeof(float));

    this->m_kernel[0] = -1;
    this->m_kernel[1] =  2;
    this->m_kernel[2] = -1;
    this->m_kernel[3] = -1;
    this->m_kernel[4] =  2;
    this->m_kernel[5] = -1;
    this->m_kernel[6] = -1;
    this->m_kernel[7] =  2;
    this->m_kernel[8] = -1;

    this->m_kernelSize = 3;
}

void Kernel::setDiagonalSXKernel() {
    free(this->m_kernel);
    this->m_kernel = (float*)calloc(9, sizeof(float));

    this->m_kernel[0] =  2;
    this->m_kernel[1] = -1;
    this->m_kernel[2] = -1;
    this->m_kernel[3] = -1;
    this->m_kernel[4] =  2;
    this->m_kernel[5] = -1;
    this->m_kernel[6] = -1;
    this->m_kernel[7] = -1;
    this->m_kernel[8] =  2;

    this->m_kernelSize = 3;
}

void Kernel::setDiagonalDXKernel() {
    free(this->m_kernel);
    this->m_kernel = (float*)calloc(9, sizeof(float));

    this->m_kernel[0] = -1;
    this->m_kernel[1] = -1;
    this->m_kernel[2] =  2;
    this->m_kernel[3] = -1;
    this->m_kernel[4] =  2;
    this->m_kernel[5] = -1;
    this->m_kernel[6] =  2;
    this->m_kernel[7] = -1;
    this->m_kernel[8] = -1;

    this->m_kernelSize = 3;
}

void Kernel::setCustomKernel(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
    free(this->m_kernel);
    this->m_kernel = (float*)calloc(9, sizeof(float));

    this->m_kernel[0] = a;
    this->m_kernel[1] = b;
    this->m_kernel[2] = c;
    this->m_kernel[3] = d;
    this->m_kernel[4] = e;
    this->m_kernel[5] = f;
    this->m_kernel[6] = g;
    this->m_kernel[7] = h;
    this->m_kernel[8] = i;

    this->m_kernelSize = 3;
}

float* Kernel::getKernel() {
    return(this->m_kernel);
}

int Kernel::getKernelSize() {
    return(this->m_kernelSize);
}

float Kernel::getBlurStrength() {
    return(this->m_gaussianBlurStrength);
}