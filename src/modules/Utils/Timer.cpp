#include "Timer.h"

Timer::Timer() {
    this->m_start = clock();
}

double Timer::getElapsed() {
    return((double)(clock() - this->m_start) / CLOCKS_PER_SEC);
}

double Timer::getElapsedCPU() {
    return((double)(clock() - this->m_start));
}

void Timer::print() {
    printf("%sTime: %.4fs\nCPU: %.0f\n%s", strBlue.c_str(), this->getElapsed(), this->getElapsedCPU(), strNoColor.c_str());
}

