#ifndef CSCM98_UTILS_H
#define CSCM98_UTILS_H

#include <chrono>

#include "RingBuffer.h"

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

public:
    Timer();
    ~Timer();

    double measure();
};

#endif // !CSCM98_UTILS_H