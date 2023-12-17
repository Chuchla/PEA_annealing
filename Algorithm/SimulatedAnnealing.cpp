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





std::pair<std::vector<int>, float> SimulatedAnnealing::RunSimulatedAnnealing(const std::string &filePath) {
    using namespace std;
    auto graph = WorkOnFiles::GetGraph(filePath);
    random_device randomDevice;
    mt19937 gen(randomDevice());
    uniform_real_distribution<> distribution(0,1);
    double worseSolution{};
    int verteciesNumber = graph.size();
    float coolingFactor{0.995};
    float eraFactor = 1;
    float tau = 0.5;
    int eraLenght = (verteciesNumber*(verteciesNumber-1))/2;
    auto currentSolution = Solution::GetRandomSolution(graph);
    auto currentDistance = Solution::GetDistance(graph,currentSolution);
    float Temp = Temperature::StartingTemperature(currentSolution,currentDistance,tau, graph);

    int iterations{};
    cout << "Starting Solution:" << currentDistance << endl;
    vector<int> bestSolution = currentSolution;
    float bestDistace = currentDistance;

    auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto workTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();


    while(workTime <= 360 and Temp > 0.0000001){
        int eraIterations{};
        while(eraIterations<=eraLenght*eraFactor){
            auto adjacentSolution = Neighborhood::Swap(currentSolution);
            auto adjacentDistance = Solution::GetDistance(graph, adjacentSolution);
            //cout << "Adjacent solution: " << adjacentDistance << " for temp: " << Temp << endl;
            worseSolution = distribution(gen);
            double delta = currentDistance - adjacentDistance;
            double eval = exp(delta/Temp);
            if(delta>0){
                currentSolution = adjacentSolution;
                currentDistance = adjacentDistance;
                //cout << "Current solution: " << currentDistance << " for temp: " << Temp << endl;
            }else if (worseSolution < eval){
                currentSolution = adjacentSolution;
                currentDistance = adjacentDistance;
                //cout << "Current solution: " << currentDistance << " for temp: " << Temp << endl;
            }
            if(bestDistace > currentDistance){
                bestSolution = currentSolution;
                bestDistace = currentDistance;
                cout << "New best solution: " << bestDistace << " for temp: " << Temp << endl;
            }
            eraIterations++;
        }
        Temp = Temperature::Geometric(Temp, coolingFactor);
        //cout << "Current solution: " << currentDistance << " for temp: " << to_string(Temp) << endl;
        currentTime = std::chrono::high_resolution_clock::now();
        workTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    }
    for(auto element : bestSolution){
        cout << element << " ";
    }
    cout << endl;
    cout << bestDistace;
    return {bestSolution, bestDistace};
}