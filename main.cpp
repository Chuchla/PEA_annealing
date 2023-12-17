#include <iostream>
#include "Utilities/WorkOnFiles.h"
#include "Algorithm/SimulatedAnnealing.h"
#include "lemon/list_graph.h"
#include "Algorithm/Parameters/Solution.h"
#include "Algorithm/Parameters/Neighborhood.h"
int main() {
    using namespace std;
    using namespace lemon;

    auto graph = WorkOnFiles::GetGraph("/home/chuchla/CLionProjects/PEA_annealing/Instances/TXT/tsp_10.txt");
    auto xd1 = SimulatedAnnealing::RunSimulatedAnnealing("/home/chuchla/CLionProjects/PEA_annealing/Utilities/Instances/NonSymetric/p43.atsp");
    return 0;
}
