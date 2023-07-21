#include "Timer.hpp"

// constructor method
Timer::Timer() {
    // intialize the timer to the moment of creation of the clock
    this->m_start = clock();
}

// get the time passed since the last reset / creation
double Timer::getElapsed() {
    return((double)(clock() - this->m_start) / CLOCKS_PER_SEC);
}

// get the number of cpu clocks since the last reset / creation
double Timer::getElapsedCPU() {
    return((double)(clock() - this->m_start));
}

// print the internal information of the clock
void Timer::print() {
    printf("%sTime: %.4fs\nCPU: %.0f\n%s", strBlue.c_str(), this->getElapsed(), this->getElapsedCPU(), strNoColor.c_str());
}

