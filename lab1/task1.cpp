#include <iostream>

void say_hello()
{
    printf("Hello world!\n");
}

// In C++, `main` is the starting point for all programs.
// It must have `argc` and `argv` as parameters, exactly as specified below.
int main(int argc, const char *argv[])
{
    // Call the `say_hello` function defined above
    say_hello();

    // In C++, we return 0 to indicate that the program has finished successfully
    return 0;
}
