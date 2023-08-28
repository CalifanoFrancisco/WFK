#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

struct Timer {

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::string fname;

    Timer(std::string functionName) {
        fname = functionName;
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << fname <<" | "<< duration.count() << "ms" << std::endl;
    }


   
};

#endif