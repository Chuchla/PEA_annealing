#include <iostream>
#include "Utilities/WorkOnFiles.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    WorkOnFiles workOnFiles;
    auto graph = workOnFiles.GetGraphFromTSPFile("C:\\Users\\GS65\\CLionProjects\\PEA_annealing\\Instances\\NonSymetric\\ft53.atsp");
    for(const auto row: graph){
        for(auto element: row){
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
