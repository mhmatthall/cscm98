#ifndef CSCM98_UTILS_H
#define CSCM98_UTILS_H

#include <chrono>

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