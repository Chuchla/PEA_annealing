#include <iostream>
#include "Utilities/WorkOnFiles.h"
int main() {
    WorkOnFiles workOnFiles;
    auto graph = workOnFiles.GetGraphFromTSPFile("/home/chuchla/CLionProjects/PEA_annealing/Instances/Symetric/gr17.tsp");
    for(const auto row: graph){
        for(auto element: row){
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
