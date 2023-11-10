#ifndef CSCM98_UTILS_H
#define CSCM98_UTILS_H

#if defined(__x86_64__) || defined(__x86_64) || defined(_X86_) || defined(__X86__) || defined(_M_X64) || defined(_M_AMD64) || defined(__amd64__) || defined(__amd64) || defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
// If x86-based target architecture, import standard x86 intrinsics
#include <xmmintrin.h>
#else
// If other target architecture (i.e. ARM), use magic translation header which converts to Neon intrinsics
#include "sse2neon.h"
#endif

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