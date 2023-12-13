//
// Created by chuchla on 06.12.23.
//

#ifndef PEA_ANNEALING_TEMPERATURE_H
#define PEA_ANNEALING_TEMPERATURE_H


class Temperature {


    float Geometric(float T, float alfa);

    float Boltzman(float T, float alfa);

    float Cauchy(float T, float alfa);

    float Linear(float T, float alfa);

    float Boltzman(float T);

    float Exponential(float T, float alfa, int iteration);

    float Logaritmic(float T, int k);

    float Boltzman(float T, float T0, int k);
};

#endif //PEA_ANNEALING_TEMPERATURE_H
