#ifndef __TIMER__
#define __TIMER__

#include <time.h>
#include "utils.h"


// class to implement a timer
class Timer {
    public:
        // constructor method
        Timer();
        // return the elapsed time since the creation of the timer
        double getElapsed();
        // return the elapsed cpu cicles since the creation of the timer
        double getElapsedCPU();
        // resets the timer to 0
        void reset();
        // print the informations of the timer
        void print();

    private:
        // internal counter for the time
        clock_t m_start;
};

#endif