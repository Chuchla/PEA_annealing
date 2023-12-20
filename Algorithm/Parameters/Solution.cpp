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
    std::vector<int> path(graph.size());

    std::iota(path.begin(), path.end(), 0);
    
    std::random_device rd;
    std::mt19937 g(rd());

    // Mieszamy miasta, aby uzyskać losową trasę
    std::shuffle(path.begin(), path.end(), g);

    return path;
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
    for (int i = 0; i < path.size()-1; i++) {
        distance += graph[path[i]][path[i + 1]];
    }
    distance+=graph[path[path.size()-1]][path[0]];
    return distance;
}

