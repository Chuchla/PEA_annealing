#include <iostream>
#include "Utilities/WorkOnFiles.h"
int main() {
    WorkOnFiles workOnFiles;
    auto graph = workOnFiles.GetGraph("/home/chuchla/CLionProjects/PEA_annealing/Instances/TXT/tsp_17.txt");
    for(const auto row: graph){
        for(auto element: row){
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
