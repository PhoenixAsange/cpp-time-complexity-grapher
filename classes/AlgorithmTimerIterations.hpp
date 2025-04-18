#ifndef ALGORITHMTIMERITERATIONS_HPP
#define ALGORITHMTIMERITERATIONS_HPP

#include "Timer.hpp"
#include "GraphDocumentGenerator.hpp"
#include <functional>
#include <sstream>

//This class runs a provided function repeatedly across interpolated iteration steps (from 1 to maxIterations), 
//times the execution, and outputs the results to both console and CSV for later plotting via matplotlib.

template<typename Function>
class AlgorithmTimerIterations : public Timer {
    private: 
        const std::string name;
        const int maxIterations;
        int steps;

    public:
        AlgorithmTimerIterations(const std::string name, Function&& function, const int maxIterations = 10000, const int steps = 20, const int trialsPerStep = 3) 
        : Timer(name), name(name), maxIterations(maxIterations), steps(steps) {

            int stepSize = (maxIterations - 1) / (steps - 1); //Interpolates values between 1 and max iterations

            for (int step = 1; step < steps; ++step) {
                int iterations = step * stepSize;
                long long totalTime = 0;

                for (int trial = 0; trial < trialsPerStep; ++trial) { //Averages time over trials per step 
                    startSubTimer();

                    for (int i = 0; i < iterations; ++i) {
                        (void)function();
                    }  

                    totalTime += this->getEndSubTimer(); //Accumulate average time for step

                    std::cout << "Done";
                    // std::cout << "Step " << step << ", trial " << trial << " (" << iterations << " iterations): " << avgTime << "ns" << std::endl; //
                }

                long long avgTime = totalTime / trialsPerStep; //Averages trials over step

                // std::cout << "Step " << step << " (" << iterations * trialsPerStep << " times): " << avgTime << "ns average" << std::endl; //Total step time
                                    
                std::ostringstream content;
                content << step << "," << iterations << "," << avgTime << "\n";
                appendItem(content.str()); //Append this steps data to csv
            }
        }
};

#endif