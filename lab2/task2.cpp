#include <iostream>
#include <thread>
#include <mutex>

#include "utils.h"

// Our global counter variable
int count = 0;

// Declare a global mutex (lock) to be used with our counter variable
std::mutex counter_lock;

// Increment our counter by ten million
void increment()
{
    for (int i = 0; i < 10'000'000; i++)
    {
        // Lock the mutex to give us exclusive access to the counter variable
        counter_lock.lock();

        // Increment the counter
        count++;

        // Unlock the mutex to release our exclusive access
        counter_lock.unlock();
    }
}

int main(int argc, const char *argv[])
{
    printf("Using a mutex:\n");

    // Start a timer to measure how long things take
    Timer timer;

    // Create an array of four threads
    std::thread threads[4];

    // Dispatch four threads to each increment our counter
    for (int i = 0; i < 4; i++)
    {
        threads[i] = std::thread(increment);
        printf("  Thread %d dispatched...\n", i);
    }

    // Join up the threads
    for (int i = 0; i < 4; i++)
    {
        threads[i].join();
    }

    // Print the final value of `count`
    printf("Final value of count = %d\n", count);
    printf("Completed in %.2f milliseconds\n", timer.measure());

    return 0;
}
