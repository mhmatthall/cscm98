#include <iostream>
#include <thread>

void say_hello_multithreaded(int thread_id)
{
    printf("  Hello world from thread %d!\n", thread_id);
}

int main(int argc, const char *argv[])
{
    printf("Single thread example:\n");

    // Dispatch a thread that will call the `say_hello_multithreaded` function
    // with `thread_id` equal to 1
    std::thread thread_example(say_hello_multithreaded, 1);

    // After we dispatch a thread, the program lets the thread run in the
    // background while the main thread continues executing. This is what
    // multithreading is all about!

    // Eventually though, we need to make sure that the thread has actually
    // finished executing before we, for example, try to use the results of
    // the thread's execution, or try to exit the program. We do this by
    // 'joining' the thread, which makes the program wait until the thread has
    // finished executing before continuing.
    thread_example.join();

    printf("Multiple thread example:\n");

    // Create an array of four threads
    std::thread threads[4];

    // Then, dispatch four threads that each call the `say_hello_multithreaded` function
    for (int i = 0; i < 4; i++)
    {
        threads[i] = std::thread(say_hello_multithreaded, i);
    }

    // Finally, join each of the threads
    for (int i = 0; i < 4; i++)
    {
        threads[i].join();
    }

    printf("End of threads example.\n");

    return 0;
}
