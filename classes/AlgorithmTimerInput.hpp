#ifndef ALGORITHMTIMERINPUT_HPP
#define ALGORITHMTIMERINPUT_HPP

#include "Timer.hpp"
#include "GraphDocumentGenerator.hpp"
#include <functional>
#include <sstream>

template<typename Function>
class AlgorithmTimerInput : public Timer {
private:
    const std::string name;
    const int maxInputs;
    int steps;
    int trialsPerStep;
    Function function;

//This class runs a provided function across an interpolated vector size in steps (from 1 to maxIterations), 
//times the execution, and outputs the results to both console and CSV for later plotting via matplotlib.

public:
    AlgorithmTimerInput(const std::string& name, Function&& function, const std::string listType = "unsorted", int maxInputs = 25000, int steps = 10, int trialsPerStep = 2) :
    Timer(name), name(name), function(function), maxInputs(maxInputs), 
    steps(steps), trialsPerStep(trialsPerStep) {

        int stepSize = (maxInputs - 1) / (steps - 1); //Interpolates values between 1 and max iterations

        for (int step = 1; step < steps; ++step) { //Run each step
            int iterations = step * stepSize; //Times to iterate function or size of vector
            long long totalTime = 0;

            for (int trial = 0; trial < trialsPerStep; ++trial) {

                //Make vector
                std::vector<int> inputs;

                if (listType == "sorted") {
                    for (int i = 0; i < iterations; ++i) {
                        inputs.push_back(i);
                    }
                }
                else if (listType == "random") {
                    for (int i = 0; i < iterations; ++i) {
                        inputs.push_back(rand());
                    }
                }
                else if (listType == "reverse") { // Reverse sorted list
                    for (int i = iterations - 1; i >= 0; --i) {
                        inputs.push_back(i);
                    }
                }
                else if (listType == "extreme") { // Extreme value distribution
                    for (int i = 0; i < iterations; ++i) {
                        if (i % 20 == 0) {
                            inputs.push_back(rand() % 100000 + 10000); // occasional large outlier
                        } else {
                            inputs.push_back(rand() % 10); // mostly small values
                        }
                    }
                }
                else if (listType == "duplicates") { // Many duplicate values
                    int values[] = {1, 2, 3, 4, 5}; // Small fixed set of values
                    for (int i = 0; i < iterations; ++i) {
                        inputs.push_back(values[rand() % 5]);
                    }
                }
                else {
                    std::cout << "Unknown" << std::endl;
                }

                //Run vector on benchmark 
                std::cout << "Done" << std::endl;
                this->startSubTimer();
                (void)function(inputs);
            
                totalTime += this->getEndSubTimer();

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