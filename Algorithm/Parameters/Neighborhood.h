//
// Created by chuchla on 15.12.23.
//

#ifndef PEA_ANNEALING_NEIGHBORHOOD_H
#define PEA_ANNEALING_NEIGHBORHOOD_H


#include <vector>

class Neighborhood {
public:



    static std::vector<int> Swap(std::vector<int> path);

    static void twoOptSwap(std::vector<int> &route, int i, int k);

    static std::vector<int> twoOptNeighbour(const std::vector<int> &currentSolution);
};


#endif //PEA_ANNEALING_NEIGHBORHOOD_H
