//
// Created by chuchla on 06.12.23.
//

#ifndef PEA_ANNEALING_TEMPERATURE_H
#define PEA_ANNEALING_TEMPERATURE_H


#include <vector>

class Temperature {

public:
    static float Geometric(float T, float alfa);

    static float Cauchy(float T, float alfa);

    static float Linear(float T, float alfa);

    static float Exponential(float T, float alfa, int iteration);

    static float Boltzman(float T, float T0, int k);

    static float StartingTemperature(std::vector<int> startingPath, float startingDistance, double tau,
                              std::vector<std::vector<float>> graph);

    static float Logaritmic(float T, float alfa, long long int k);
};

#endif //PEA_ANNEALING_TEMPERATURE_H
