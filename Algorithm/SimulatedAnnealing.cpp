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





std::pair<std::vector<int>, float> SimulatedAnnealing::RunSimulatedAnnealing(const std::string &filePath) {
    auto grpah = WorkOnFiles::GetGraph(filePath);



    return {{0}, 0};
}