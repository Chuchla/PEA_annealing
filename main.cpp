#include <iostream>
#include "Utilities/WorkOnFiles.h"
#include "Algorithm/SimulatedAnnealing.h"
#include "lemon/list_graph.h"
#include "Algorithm/Parameters/Solution.h"
int main() {
    using namespace std;
    using namespace lemon;

    auto graph = WorkOnFiles::GetGraph("/home/chuchla/CLionProjects/PEA_annealing/Instances/TXT/tsp_6_1.txt");
    for(auto row : graph){
        for(auto element : row){
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    auto randomSol = Solution::GetRandomSolution(graph);
    for(auto element : randomSol){
        std::cout << element << " ";
    }
    auto distance = Solution::GetDistance(graph ,randomSol);
    std::cout << std::endl << distance;
    return 0;
}
