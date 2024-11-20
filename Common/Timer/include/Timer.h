#ifndef TIMER_H
#define TIMER_H


#include <iostream>
#include <chrono>


class Timer {
public:
    Timer() {
        start_time_point_ = std::chrono::high_resolution_clock::now();     
    }
    ~Timer() {
        stop();
    }
    void stop();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point_;
};

#endif //TIMER_H