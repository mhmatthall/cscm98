#include "utils.h"

Timer::Timer() : start_time(std::chrono::high_resolution_clock::now()){};

Timer::~Timer(){};

// Returns the time in milliseconds since the timer was created
double Timer::measure()
{
    const auto end_time = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> delta = end_time - start_time;
    return delta.count();
};
