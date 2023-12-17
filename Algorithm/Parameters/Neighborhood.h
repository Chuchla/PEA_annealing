//
// Created by chuchla on 15.12.23.
//

#ifndef PEA_ANNEALING_NEIGHBORHOOD_H
#define PEA_ANNEALING_NEIGHBORHOOD_H


#include <vector>

class Neighborhood {
public:

    static std::vector<int> TwoOpt(std::vector<int> path);

    static std::vector<int> Swap(std::vector<int> path);
};


#endif //PEA_ANNEALING_NEIGHBORHOOD_H
