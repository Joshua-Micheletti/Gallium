#pragma once

#define PI 3.1415926535
#define Em 2.71828

class Kernel {
	public:
		Kernel();

		void setGaussianKernel(float, int);
		void setEdgeDetectionKernel();
		void setSharpeningKernel();
		void setBoxBlurKernel(int);
		void setEmbossKernel();
		void setHorizontalKernel();
		void setVerticalKernel();
		void setDiagonalSXKernel();
		void setDiagonalDXKernel();
		void setCustomKernel(float, float, float, float, float, float, float, float, float);

		float* getKernel();
		int getKernelSize();
		float getBlurStrength();

	private:
		float* kernel;
		int kernelSize;
		float gaussianBlurStrength;
};