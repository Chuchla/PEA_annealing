#include <iostream>
#include "Utilities/WorkOnFiles.h"
#include "Algorithm/SimulatedAnnealing.h"
#include "lemon/list_graph.h"
#include "Algorithm/Parameters/Solution.h"
#include "Algorithm/Parameters/Neighborhood.h"
#include "Utilities/Test.h"
int main() {
    using namespace std;

    //auto xd1 = SimulatedAnnealing::RunSimulatedAnnealing("/home/chuchla/CLionProjects/PEA_annealing/Utilities/Instances/NonSymetric/kro124p.atsp");
    //auto xd1 = SimulatedAnnealing::RunSimulatedAnnealing("/home/chuchla/CLionProjects/PEA_annealing/Utilities/Instances/Symetric/pr299.tsp");


    //WorkOnFiles::WriteToCSV("ftv55.csv", xd1);
    Test::TestSimulatedAnnealing("/home/chuchla/CLionProjects/PEA_annealing/danetsp.ini");

    return 0;
}
