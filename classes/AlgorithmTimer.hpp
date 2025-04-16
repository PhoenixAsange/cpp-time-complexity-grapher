#ifndef ALGORITHMTIMER_HPP
#define ALGORITHMTIMER_HPP

#include "Timer.hpp"
#include "GraphDocumentGenerator.hpp"
#include <functional>
#include <sstream>

//This template class runs a provided function repeatedly across interpolated iteration steps (from 1 to maxIterations), 
//times the execution, and outputs the results to both console and CSV for later plotting via matplotlib.

template<typename Function>
class AlgorithmTimer : public Timer {
    private: 
        const std::string name;
        const int maxIterations;
        int steps;

    public:
        AlgorithmTimer(const std::string name, const int maxIterations, const int steps, Function&& function) 
        : Timer(name), name(name), maxIterations(maxIterations), steps(steps) {
            int stepSize = (maxIterations - 1) / (steps - 1); //Interpolates values between 1 and max iterations
            
            for (int step = 1; step < steps; ++step) {
                int iterations = step * stepSize;

                for (int i = 0; i < iterations; ++i) { //One step
                    (void)function();
                }  
                std::cout << "Step " << step << " (" << iterations << " times): " << this->getTimeNS() << "ns" << std::endl;
                                    
                std::ostringstream content;
                content << step << "," << iterations << "," << this->getTimeNS() << "\n";
                appendItem(content.str()); //Append this steps data to csv
            }
            std::cout << "Time to run " << maxIterations << " times: " << this->getTimeNS() << "ns" << std::endl; 
        }
};

#endif