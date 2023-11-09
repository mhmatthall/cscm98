#include <iostream>
#include <thread>

#include "utils.h" // For our Timer class

// Calculate the Leibniz series estimation of pi
// - start: The term to start calculating from (default 1)
// - result: A pointer to a variable to store the result in
// - limit: The term to stop calculating at
void leibnizSeries(int limit, double *result, int start = 0)
{
    double sum = 0.0;

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

int main(int argc, const char *argv[])
{
    // In C++, we can use the ' character to separate groups of digits in a
    // number to make it easier to read.
    int limit = 100'000'000;

    // Start a timer to measure how long things take
    Timer without_mt_timer;

    // Estimate pi using the Leibniz series, without multithreading
    printf("Without multithreading:\n");

    // In this task, we're using a slightly different way of getting a result
    // from a function. Instead of assigning the result to a variable, we're
    // passing a pointer to a variable to the function, and the function will
    // assign the result to that variable. This is useful when we want to get
    // multiple results from a function, which will be useful later.

    // Basically:
    //      double pi = leibnizSeries(limit);
    // is equivalent to:
    //      double pi = 0.0;
    //      leibnizSeries(limit, &pi);

    double pi = 0.0;
    leibnizSeries(limit, &pi);

    // Multiply the sum by 4 to get the final result, as per the formula
    pi *= 4;

    printf("  Estimated pi as approximately %.15f in %.2f milliseconds.\n\n", pi, without_mt_timer.measure());

    // Estimate pi using the Leibniz series using multiple threads
    printf("With multithreading:\n");

    // Start a new timer
    Timer with_mt_timer;

    // Create an array of four threads
    std::thread threads[4];

    // Create an array for storing our partial results from each thread
    double pi_parts[4];

    // Split up the Leibniz series calculation into four piecewise components
    // - Thread 0 will calculate the series from:               0 to (limit / 4)
    // - Thread 1 will calculate the series from:     (limit / 4) to (2 * limit / 4)
    // - Thread 2 will calculate the series from: (2 * limit / 4) to (3 * limit / 4)
    // - Thread 3 will calculate the series from: (3 * limit / 4) to limit
    for (int i = 0; i < 4; i++)
    {
        threads[i] = std::thread(
            leibnizSeries,       // Function to execute
            (i + 1) * limit / 4, // Limit term
            &pi_parts[i],        // Result
            i * limit / 4        // Start term
        );
    }

    // Join up the threads
    for (int i = 0; i < 4; i++)
    {
        threads[i].join();
    }

    // Add up the partial results from each thread
    double pi_multithreaded = 0.0;

    for (int i = 0; i < 4; i++)
    {
        pi_multithreaded += pi_parts[i];
    }

    // Multiply the sum by 4 to get the final result, as per the formula
    pi_multithreaded *= 4;

    printf("  Estimated pi as approximately %.15f in %.2f milliseconds.\n\n", pi, with_mt_timer.measure());

    return 0;
}