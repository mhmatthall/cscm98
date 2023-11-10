#include <iostream>

#include "utils.h"  // Imports our x86 intrinsics

int main(int argc, const char *argv[])
{
    // Initialise two vectors
    __m128 vector_one = _mm_set_ps(1, 2, 3, 4);
    __m128 vector_two = _mm_set_ps(5, 6, 7, 8);

    // Sum the vectors
    __m128 sum = _mm_add_ps(vector_one, vector_two);

    // Extract the results into an array of floats
    float results[4];
    _mm_storeu_ps(results, sum);

    // Print the values (notice they are in reverse order!)
    printf("sum = { %.2f, %.2f, %.2f, %.2f }\n", results[0], results[1], results[2], results[3]);

    return 0;
}
