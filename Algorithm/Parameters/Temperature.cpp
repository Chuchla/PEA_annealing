//
// Created by chuchla on 06.12.23.
// k - number of iterations
// alfa - cooling const
// T - temperature
//

#include "Temperature.h"
#include <math.h>

float Temperature::Geometric(float T, float alfa) {
    return T * alfa;
}

float Temperature::Boltzman(float T, float T0, int k) {
    float alfa{(T - T0) / (k * T0 * T)};
    return (T) / (1 + alfa * T);
}

float Temperature::Cauchy(float T, float alfa) {
    return 0;
}

float Temperature::Linear(float T, float constant) {
    return T - constant;
}

float Temperature::Exponential(float T, float alfa, int k) {
    return powf(alfa, k) * T;
}

float Temperature::Logaritmic(float T, int k) {
    return (T) / (1 + log(1 + k));
}

