#include <iostream>

#include "utils.h"

void add_floats_simd(__m128 a, __m128 b, float *results)
{
    // Add the two vectors
    __m128 sum = _mm_add_ps(a, b);

    // Copy the sum to our results variable
    _mm_store_ps(results, sum);
}

void subtract_floats_simd(__m128 a, __m128 b, float *results)
{
    // Add the two vectors
    __m128 sum = _mm_sub_ps(a, b);

    // Copy the sum to our results variable
    _mm_store_ps(results, sum);
}

void multiply_floats_simd(__m128 a, __m128 b, float *results)
{
    // Mutiply the two vectors
    __m128 sum = _mm_mul_ps(a, b);

    // Copy the sum to our results variable
    _mm_store_ps(results, sum);
}

void divide_floats_simd(__m128 a, __m128 b, float *results)
{
    // Divide the two vectors
    __m128 sum = _mm_div_ps(a, b);

    // Copy the sum to our results variable
    _mm_store_ps(results, sum);
}

int main(int argc, const char *argv[])
{
    // Instantiate two vectors
    __m128 vector_a = _mm_set_ps(2, 3, 4, 5);
    __m128 vector_b = _mm_set_ps(4, 5, 6, 7);
    
    // Create a results array
    float results[4];

    // Addition
    add_floats_simd(vector_a, vector_b, results);
    printf("Adding two floats:\n  = { %.5f, %.5f, %.5f, %.5f }\n", results[0], results[1], results[2], results[3]);

    // Subtraction
    subtract_floats_simd(vector_a, vector_b, results);
    printf("Subtracting two floats:\n  = { %.5f, %.5f, %.5f, %.5f }\n", results[0], results[1], results[2], results[3]);

    // Multiplication
    multiply_floats_simd(vector_a, vector_b, results);
    printf("Multiplying two floats:\n  = { %.5f, %.5f, %.5f, %.5f }\n", results[0], results[1], results[2], results[3]);

    // Division
    divide_floats_simd(vector_a, vector_b, results);
    printf("Dividing two floats:\n  = { %.5f, %.5f, %.5f, %.5f }\n", results[0], results[1], results[2], results[3]);

    return 0;
}
