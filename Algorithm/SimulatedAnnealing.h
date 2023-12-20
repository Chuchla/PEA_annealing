//
// Created by GS65 on 14.11.2023.
//

#ifndef PEA_ANNEALING_SIMULATEDANNEALING_H
#define PEA_ANNEALING_SIMULATEDANNEALING_H


#include <utility>
#include <string>
#include <vector>
using namespace std;
class SimulatedAnnealing {


public:
    static vector<tuple<int, long long int, float, float, std::vector<int>>> RunSimulatedAnnealing(const std::string &filePath);


    std::pair<std::vector<int>, float> Christofides(std::vector<std::vector<float>> graph);

    pair<vector<int>, float> Prim(vector<std::vector<float>> graph);

    std::pair<std::vector<int>, float> getRandomSolution(vector<vector<float>>);

};


#endif //PEA_ANNEALING_SIMULATEDANNEALING_H
