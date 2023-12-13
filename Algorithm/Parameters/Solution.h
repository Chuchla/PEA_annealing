//
// Created by chuchla on 06.12.23.
//

#ifndef PEA_ANNEALING_SOLUTION_H
#define PEA_ANNEALING_SOLUTION_H


#include <utility>
#include <vector>

class Solution {
public:
    static std::vector<int> GetRandomSolution(const std::vector<std::vector<float>> &graph);

    static float GetDistance(const std::vector<std::vector<float>> &graph, const std::vector<int> &path);


   static std::vector<int> GetGreedySolution(const std::vector<std::vector<float>> &graph);

    static std::pair<std::vector<int>, float> Prim(std::vector<std::vector<float>> graph);

    std::pair<std::vector<int>, float> Christofides(std::vector<std::vector<float>> graph);

    std::vector<int> OddVertecies(std::vector<int> mst);
};


#endif //PEA_ANNEALING_SOLUTION_H
