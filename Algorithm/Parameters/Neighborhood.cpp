//
// Created by chuchla on 15.12.23.
//

#include "Neighborhood.h"
#include <vector>
#include <random>
#include <memory>
using namespace std;

vector<int> Neighborhood::Swap(vector<int> path){
    auto size = path.size();
    random_device randomDevice;
    mt19937 gen(randomDevice());
    uniform_int_distribution<int> distribution(0, size-1);
    //ABCDEFG
    vector<bool> edgeTaken(size, false);
    vector<int> references{};
    for (int i = 0; i < 2; i++) {
        int vertex = numeric_limits<int>::infinity();
        do {
            vertex = distribution(gen);
        } while (edgeTaken[vertex] == true);
        edgeTaken[vertex] = true;
        references.push_back(vertex);
    }

    vector<int> Edge(path.begin(), path.end());
    Edge[references[0]] = path[references[1]];
    Edge[references[1]] = path[references[0]];

    return Edge;


}
vector<int> Neighborhood::TwoOpt(vector<int> path){
    //
    return {};
}