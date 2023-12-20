//
// Created by GS65 on 14.11.2023.
//

#include "SimulatedAnnealing.h"
#include "../Utilities/WorkOnFiles.h"
#include "Parameters/Solution.h"
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include "lemon/list_graph.h"
#include <map>
#include <chrono>
#include "Parameters/Neighborhood.h"
#include <random>
#include "Parameters/Temperature.h"
#include <tuple>

std::vector<std::tuple<int, long long, float, float, std::vector<int>>> SimulatedAnnealing::RunSimulatedAnnealing(const std::string &filePath) {
    std::vector<std::tuple<int, long long, float, float, std::vector<int>>> retVec;

    auto graph = WorkOnFiles::GetGraph(filePath);
    int verteciesNumber = graph.size();
    float coolingFactor{0.995};
    float eraFactor = 1;
    float tau = 0.5;
    int eraLenght = (verteciesNumber * (verteciesNumber - 1)) / 2;
    long long iterations{};

    //auto currentSolution = Solution::GetRandomSolution(graph);
    auto currentSolution = Solution::GetGreedySolution(graph);
    auto currentDistance = Solution::GetDistance(graph, currentSolution);
    float Temp = Temperature::StartingTemperature(currentSolution, currentDistance, tau, graph);
    std::vector<int> bestSolution = currentSolution;
    float bestDistace = currentDistance;
    cout << "Starting Solution:" << currentDistance << endl;

    random_device randomDevice;
    mt19937 gen(randomDevice());
    uniform_real_distribution<> distribution(0, 1);
    double worseSolution{};


    auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto workTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

    retVec.push_back({iterations,workTime,Temp,bestDistace, bestSolution});
    while (workTime <= 3600000 and Temp > 0.01 ) {
        int eraIterations{};
        while (eraIterations <= eraLenght * eraFactor) {
            vector<int> adjacentSolution;
            adjacentSolution = Neighborhood::twoOptNeighbour(currentSolution);
            //adjacentSolution = Neighborhood::Swap(currentSolution);
            auto adjacentDistance = Solution::GetDistance(graph, adjacentSolution);
            //cout << "Adjacent solution: " << adjacentDistance << " for temp: " << Temp << endl;
            worseSolution = distribution(gen);
            double delta = currentDistance - adjacentDistance;
            double eval = exp(delta / Temp);
            if (delta > 0) {
                currentSolution = adjacentSolution;
                currentDistance = adjacentDistance;
                //cout << "Current solution: " << currentDistance << " for temp: " << Temp << endl;
            } else if (worseSolution < eval) {
                currentSolution = adjacentSolution;
                currentDistance = adjacentDistance;
                //cout << "Current solution: " << currentDistance << " for temp: " << Temp << " for eval: "
                     //<< to_string(eval) << endl;
            }
            if (bestDistace > currentDistance) {
                bestSolution = currentSolution;
                bestDistace = currentDistance;
                currentTime = std::chrono::high_resolution_clock::now();
                workTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
                retVec.push_back({iterations,workTime,Temp,bestDistace, bestSolution});
                cout << "New best solution: " << bestDistace << " for temp: " << Temp << endl;
            }
            eraIterations++;


        }
        iterations++;
        //Temp = Temperature::Geometric(Temp, coolingFactor);
        //Temp = Temperature::Linear(Temp, 0.005);
        Temp = Temperature::Logaritmic(Temp,coolingFactor, iterations);
        //cout << "Current solution: " << currentDistance << " for temp: " << to_string(Temp) << endl;
        currentTime = std::chrono::high_resolution_clock::now();
        workTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
    }
    for (auto element: bestSolution) {
        cout << element << " ";
    }
    cout << endl;
    cout << bestDistace << endl << to_string(Temp) << endl;
    return retVec;
}