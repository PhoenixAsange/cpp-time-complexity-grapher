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
        std::chrono::high_resolution_clock::time_point stepTime;

    public:
        Timer(const std::string& name) : GraphDocumentGenerator(name) {
            startTime = std::chrono::high_resolution_clock::now(); //Initializes time at object construction 
        } 

        void startSubTimer() {
            stepTime = std::chrono::high_resolution_clock::now(); // Stores current time in the class member
        }

        long long getEndSubTimer() const {
            std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now(); //Stores time when called
            return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - stepTime).count(); //Calculates time from step time
        }
};

#endif