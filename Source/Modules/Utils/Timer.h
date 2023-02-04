#ifndef __TIMER__
#define __TIMER__

#include <time.h>
#include "utils.h"

class Timer {
public:
    Timer();
    double getElapsed();
    double getElapsedCPU();
    void reset();

    void print();

private:
    clock_t m_start;
};

#endif