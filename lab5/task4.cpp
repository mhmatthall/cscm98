#include <iostream>

#include "utils.h"

/*
    Calculate the Leibniz series estimation of pi.
    `start`: The term to start calculating from (default 0)
    `result`: A pointer to a float to store the result in
    `limit`: The term to stop calculating at
*/
void leibniz_series(int limit, float *result, int start = 0)
{
    float sum = 0.0;

    // Calculate the series from the start to the limit
    for (int i = start; i < limit; i++)
    {
        if (i % 2 == 0)
        {
            sum += 1.0 / (2 * i + 1);
        }
        else
        {
            sum -= 1.0 / (2 * i + 1);
        }
    }

    *result = sum;
}

/*
    Calculate the Leibniz series estimation of pi, optimised with SIMD intrinsics (uses SSE).
    `start`: The term to start calculating from (default 0)
    `result`: A pointer to a float to store the result in
    `limit`: The term to stop calculating at
*/
void leibniz_series_simd(int limit, float *result, int start = 0)
{
    // TODO: Implement this function!
}

int main(int argc, const char *argv[])
{
    // Define an iteration limit for our Leibniz calculation
    int limit = 100'000'000;

    printf("Without SIMD intrinsics:\n");

    Timer without_simd_timer;

    float pi = 0.0;
    leibniz_series(limit, &pi);

    // Multiply the sum by 4 to get the final result, as per the formula
    pi *= 4;

    printf("  Estimated pi as approximately %.15f in %.2f milliseconds.\n\n", pi, without_simd_timer.measure());

    printf("With SIMD intrinsics:\n");

    Timer with_simd_timer;

    float pi_simd = 0.0;
    leibniz_series_simd(limit, &pi);

    // Multiply the sum by 4 to get the final result, as per the formula
    pi_simd *= 4;

    printf("  Estimated pi as approximately %.15f in %.2f milliseconds.\n\n", pi_simd, with_simd_timer.measure());

    return 0;
}
