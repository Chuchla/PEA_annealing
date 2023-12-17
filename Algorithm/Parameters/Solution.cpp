//
// Created by chuchla on 06.12.23.
//

#include "Solution.h"
#include <vector>
#include <random>
#include <limits>
#include <algorithm>
#include <queue>
#include <map>


std::vector<int> Solution::GetRandomSolution(const std::vector<std::vector<float>> &graph) {
    int numberOfVertecies = graph.size();
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<int> distribution(0, numberOfVertecies - 1);
    std::vector<bool> verteciesInPath(numberOfVertecies, false);
    std::vector<int> randomPath;

    int vistied = distribution(gen);
    randomPath.push_back(vistied);
    verteciesInPath[vistied] = true;

    for (int i = 1; i < numberOfVertecies; i++) {
        std::vector<int> nextPossible;
        for (int j = 0; j < numberOfVertecies; j++) {
            if (graph[vistied][j] && graph[vistied][j] != std::numeric_limits<float>::infinity() &&
                !verteciesInPath[j]) {
                nextPossible.push_back(j);
            }
        }
        if (nextPossible.empty()) break;

        std::uniform_int_distribution<int> dis(0, nextPossible.size() - 1);
        vistied = nextPossible[dis(gen)];
        randomPath.push_back(vistied);
        verteciesInPath[vistied] = true;
    }

    return randomPath;
}

std::vector<int> Solution::GetGreedySolution(const std::vector<std::vector<float>> &graph) {
    using namespace std;
    int verteciesNumber = graph.size();
    vector<int> greedyPath;
    vector<bool> isInPath(verteciesNumber, false);

    int vertex{};
    isInPath[vertex] = true;
    greedyPath.push_back(vertex);

    for (int i = 0; i < verteciesNumber; i++) {
        vector<float> row = graph[vertex];
        for (int j = 0; j < verteciesNumber; j++) {
            auto iterator = min_element(row.begin(), row.end());
            ptrdiff_t index = distance(row.begin(), iterator);
            if (isInPath[index] == false) {
                isInPath[index] = true;
                greedyPath.push_back(index);
                vertex = index;
                break;
            } else {
                row[index] = numeric_limits<float>::infinity();
                continue;
            }
        }
    }

    return greedyPath;
}

float Solution::GetDistance(const std::vector<std::vector<float>> &graph, const std::vector<int> &path) {
    float distance{};
    for (int i = 0; i < path.size() - 1; i++) {
        distance += graph[path[i]][path[i + 1]];
    }
    distance+=graph[path.size()-1][path[0]];
    return distance;
}

