#include <iostream>
#include <thread>

#include <unistd.h> // For `sleep`

#include "utils.h"  // For our Timer class

// Example of a function that takes a long time to execute
void really_complicated_task(int task_id)
{
    printf("  Executing really complicated task #%d...\n", task_id);
    sleep(2);
}

int main(int argc, const char *argv[])
{
    printf("Without multithreading:\n");

    // Start a timer to measure how long things take
    Timer without_mt_timer;

    // Execute the really complicated task four times
    for (int i = 0; i < 4; i++)
    {
        really_complicated_task(i);
    }

    // Stop the timer and print the result
    printf("All tasks completed in %.2f milliseconds.\n\n", without_mt_timer.measure());

    printf("With multithreading:\n");

    // Start a new timer
    Timer with_mt_timer;

    // Create an array of four threads
    std::thread threads[4];

    // Then, execute the really complicated task four times in parallel threads
    for (int i = 0; i < 4; i++)
    {
        threads[i] = std::thread(really_complicated_task, i);
    }

    // Finally, join up the threads
    for (int i = 0; i < 4; i++)
    {
        threads[i].join();
    }

    printf("All tasks completed in %.2f milliseconds.\n\n", with_mt_timer.measure());

    return 0;
}
