#include <iostream>

#if defined(__x86_64__) || defined(__x86_64) || defined(_X86_) || defined(__X86__) || defined(_M_X64) || defined(_M_AMD64) || defined(__amd64__) || defined(__amd64) || defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
// If x86-based target architecture
#include <xmmintrin.h>
#else
// If other target architecture (ARM)
#include "sse2neon.h"
#endif

int main(int argc, const char *argv[])
{
    // Initialise two vectors
    __m128 vector_one = _mm_set_ps(1, 2, 3, 4);
    __m128 vector_two = _mm_set_ps(5, 6, 7, 8);

    // Sum the vectors
    __m128 sum = _mm_add_ps(vector_one, vector_two);

    // Extract the results as four `float` values
    float *results = (float *)&sum;

    // Print the values
    printf("sum = {%.2f, %.2f, %.2f, %.2f}\n", results[0], results[1], results[2], results[3]);

    return 0;
}
