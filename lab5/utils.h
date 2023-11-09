#ifndef CSCM98_UTILS_H
#define CSCM98_UTILS_H

// If using x86_64, import SSE intrinsics
#ifdef __x86_64__

#include <immintrin.h>

// If using ARM, import Neon intrinsics (via sse2neon mapping)
#else

#include "sse2neon.h"

#endif // !__x86_64__

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