#include "Timer.h"

void Timer::stop() {
    auto end_time = std::chrono::high_resolution_clock::now();
    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point_).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time).time_since_epoch().count();
    auto duration  = end - start;
    double ms  = duration * 0.001;
    std::cout << duration << "us (" << ms << "ms)" << std::endl;
}