#include <iostream>
#include "Utilities/WorkOnFiles.h"
int main() {
    WorkOnFiles workOnFiles;
    auto graph = workOnFiles.GetGraph("/home/chuchla/CLionProjects/PEA_annealing/Instances/NonSymetric/kro124p.atsp");
    for(const auto row: graph){
        for(auto element: row){
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
