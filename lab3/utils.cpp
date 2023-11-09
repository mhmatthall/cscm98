#include "utils.h"

void sleep_thread(int milliseconds_to_wait)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_wait));
}

Timer::Timer() : start_time(std::chrono::high_resolution_clock::now()){};

Timer::~Timer(){};

// Returns the time in milliseconds since the timer was created
double Timer::measure()
{
    const auto end_time = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> delta = end_time - start_time;
    return delta.count();
};

SimpleSet::SimpleSet(){};

SimpleSet::~SimpleSet()
{
    set.clear();
};

// Add an integer to the set
void SimpleSet::insert(int value)
{
    set.insert(value);
};

// Remove an integer from the set
void SimpleSet::remove(int value)
{
    set.erase(value);
};

// Return the set elements as a formatted string, e.g. `{ 1, 2, 3 }`
std::string SimpleSet::to_string()
{
    std::string output = "{ ";

    for (auto iter = set.begin(); iter != set.end(); ++iter)
    {
        output += std::to_string(*iter);
        output += ", ";
    }

    output += "}";

    return output;
};

// Return the number of elements in the set
int SimpleSet::size()
{
    return set.size();
}

// Return a random number from the set
// Derived from: https://stackoverflow.com/a/3052796
int SimpleSet::select_random()
{
    // Generate a random index number
    int index = rand() % set.size();

    // Iterate through to that element
    auto iterator = std::begin(set);
    std::advance(iterator, index);

    // Return the element at that index
    return *iterator;
}