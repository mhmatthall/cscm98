#include <iostream>
#include <thread>
#include <atomic>

#include "utils.h"

// Now let's make our global counter variable atomic
std::atomic<int> count;

// Increment the counter by ten million
void increment()
{
    for (int i = 0; i < 10'000'000; i++)
    {
        // Use the atomic `fetch_add()` method to increment the counter
        // This fetches the current counter value and adds 1 in a single atomic operation
        count.fetch_add(1);
    }
}

int main(int argc, const char *argv[])
{
    printf("Using atomic functions:\n");

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

    // Print the final value of `count` using the atomic `load()` method
    printf("Final value of count = %d\n", count.load());
    printf("Completed in %.2f milliseconds\n", timer.measure());

    return 0;
}
