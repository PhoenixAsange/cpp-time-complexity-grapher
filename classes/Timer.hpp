#ifndef TIMER_HPP
#define TIMER_HPP

#include "GraphDocumentGenerator.hpp"
#include <string>
#include <iostream>
#include <chrono>

//Lightweight timer script that starts time on object construction 
//to avoid function calls during algorithm timing

class Timer : public GraphDocumentGenerator {
    private:
        std::chrono::high_resolution_clock::time_point startTime;

    public:
        Timer(const std::string& name) : GraphDocumentGenerator(name) {
            startTime = std::chrono::high_resolution_clock::now(); //Initializes time at object construction 
        } 

        long long getTimeNS() { //Timer ends on object destruction
            std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now(); 
            return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count(); 
        }
};

#endif