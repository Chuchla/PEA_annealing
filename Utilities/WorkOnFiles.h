//
// Created by GS65 on 14.11.2023.
//

#ifndef PEA_ANNEALING_WORKONFILES_H
#define PEA_ANNEALING_WORKONFILES_H

#include <vector>
#include <string>
class WorkOnFiles{
public:
    WorkOnFiles();

    std::vector<std::vector<float>> GetGraphFromTSPFile(const std::string& filePath);

};
#endif //PEA_ANNEALING_WORKONFILES_H
