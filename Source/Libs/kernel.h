#pragma once

#define PI 3.1415926535
#define Em 2.71828

class Kernel {
	public:
		Kernel();

		float *getGaussianKernel(float, int);
		float* getEdgeDetectionKernel();
		float* getSharpeningKernel();
		float* getBoxBlurKernel(int);
};