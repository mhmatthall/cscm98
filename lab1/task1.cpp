#include <iostream>

void sayHello()
{
    printf("Hello world!\n");
}

// In C++, `main` is the starting point for all programs.
// It must have `argc` and `argv` as parameters, exactly as specified below.
int main(int argc, const char *argv[])
{
    // Call the `sayHello` function defined above
    sayHello();

    // In C++, we return 0 to indicate that the program has finished successfully
    return 0;
}
