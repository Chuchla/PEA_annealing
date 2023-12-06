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



    std::pair<std::vector<int>, float> RunSimulatedAnnealing(const std::string &filePath);
public:

    std::pair<std::vector<int>, float> Christofides(std::vector<std::vector<float>> graph);

    pair<vector<int>, float> Prim(vector<std::vector<float>> graph);

    std::pair<std::vector<int>, float> getRandomSolution(vector<vector<float>>);


    vector<int> OddVertecies(vector<std::vector<float>> mst);

    vector<int> OddVertecies(vector<int> mst);
};


#endif //PEA_ANNEALING_SIMULATEDANNEALING_H
