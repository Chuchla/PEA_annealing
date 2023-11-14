//
// Created by GS65 on 14.11.2023.
//
#include <algorithm>
#include "WorkOnFiles.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
//Czytanie grafu z xml
//Czytanie grafu z txt

WorkOnFiles::WorkOnFiles() {}


std::vector<std::vector<float>> WorkOnFiles::GetGraphFromTSPFile(const std::string &filePath) {
    std::ifstream file(filePath);
    std::string line;
    std::vector<std::vector<float>> graph;
    bool startReading{};
    int numberOfVertecies{};
    std::vector<float> row;
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku");
    }
    while (std::getline(file, line)) {
        if (line.find("DIMENSION: ") != std::string::npos) {
            auto found = line.find("DIMENSION:");
            std::istringstream iss(line.substr(found + 10));
            iss >> numberOfVertecies;
            std::cout << numberOfVertecies << std::endl;
            continue;
        }

        if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos) {
            startReading = true;
        }
        if (startReading and
            ((line.find("EOS")) != std::string::npos or (line.find("DISPLAY_DATA_SECTION")) != std::string::npos)) {
            break;
        }
        if (startReading) {
            std::istringstream iss(line);
            float weight;
            while (iss >> weight) {
                //New row
                if(weight > 9001) weight = std::numeric_limits<float>::infinity();
                if (row.size() == numberOfVertecies) {
                    graph.push_back(row);
                    row.erase(row.begin(), row.end());
                    row.push_back(weight);

                } else {
                    row.push_back(weight);
                }


            }
        }


    }
    graph.push_back(row);
    return graph;
}


