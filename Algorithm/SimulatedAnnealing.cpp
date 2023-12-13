//
// Created by GS65 on 14.11.2023.
//

#include "SimulatedAnnealing.h"
#include "../Utilities/WorkOnFiles.h"
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include "lemon/list_graph.h"
#include <map>



std::pair<std::vector<int>, float> SimulatedAnnealing::Prim(vector<std::vector<float>> graph){
    std::pair<std::vector<int>, float> mst;
    int verteciesNumber = graph.size();
    std::vector<int> parent(verteciesNumber, -1);
    std::vector<float> key(verteciesNumber, std::numeric_limits<float>::infinity());
    std::vector<bool> inMST(verteciesNumber,false);
    std::priority_queue<std::pair<float,int>, std::vector<std::pair<float,int>>, std::greater<>> queue;
    int src{};
    float srcWeight{};
    queue.push({srcWeight,src});
    while(!queue.empty()){
        int u = queue.top().second;
        queue.pop();
        inMST[u] = true;

        for(int v = 0 ; v < verteciesNumber; v++){
            if(!inMST[v] && graph[u][v] < key[v]){
                key[v] = graph[u][v];
                queue.push({key[v], v});
                parent[v] = u;
            }
        }
    }
    float totalWeight{};
    for(int i = 1 ; i < verteciesNumber; i++){
        totalWeight += graph[parent[i]][i];
    }
    mst.first = parent;
    mst.second = totalWeight;
    return mst;
}
std::pair<std::vector<int>, float> SimulatedAnnealing::Christofides(std::vector<std::vector<float>> graph) {
    auto getMst = Prim(graph);
    auto dym  = OddVertecies(getMst.first);

    return {};
}
std::vector<int> SimulatedAnnealing::OddVertecies(std::vector<int> mst){
    std::map<int,int> verteciesDegree;
mst.erase(mst.begin());
    for (int i = 0; i < mst.size(); ++i) {
        verteciesDegree.insert_or_assign(mst[i], 0);
    }

}

std::pair<std::vector<int>,float> SimulatedAnnealing::getRandomSolution(vector<vector<float>> graph){
    return {};
}
std::pair<std::vector<int>, float> SimulatedAnnealing::RunSimulatedAnnealing(const std::string &filePath) {
    auto grpah = WorkOnFiles::GetGraph(filePath);



    return {{0}, 0};
}