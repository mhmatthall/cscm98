#ifndef CSCM98_UTILS_H
#define CSCM98_UTILS_H

#include <chrono>
#include <set>
#include <string>
#include <thread>

void sleep_thread(int milliseconds_to_wait);

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

public:
    Timer();
    ~Timer();

    double measure();
};

class SimpleSet
{
private:
    std::set<int> set;

public:
    SimpleSet();
    ~SimpleSet();

    void insert(int value);
    void remove(int value);
    std::string toString();
    int size();
    int selectRandom();
};

#endif // !CSCM98_UTILS_H