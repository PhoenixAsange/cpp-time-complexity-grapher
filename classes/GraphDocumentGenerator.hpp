#ifndef GRAPHDOCUMENTGENERATOR_HPP
#define GRAPHDOCUMENTGENERATOR_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

//
//

class GraphDocumentGenerator {
    private:
        const std::string name;
        std::ofstream file;
    public:
        GraphDocumentGenerator(const std::string& name) : name(name) {
            std::string basePath = "../cpp-time-complexity-grapher/graph-documents/";
            std::filesystem::create_directories(basePath);
    
            // Full path + file name
            std::string fullPath = basePath + name + ".csv";
            file.open(fullPath);
            file << "step,iterations,time\n"; 
        }

        ~GraphDocumentGenerator() {
            if (file.is_open()) {
                file.close();
            }
        }

        void appendItem(std::string content) { //append single data
            if (file.is_open()) {
                file << content;
            }
        }

};

#endif