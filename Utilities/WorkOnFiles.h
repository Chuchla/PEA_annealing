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

    std::vector<std::vector<float>> ReadingFromFullMatrix(const std::string &filePath);

    std::vector<std::vector<float>> FullMatrix(const std::string &filePath);

    std::vector<std::vector<float>> EUC2D();

    std::vector<std::vector<float>> EUC2D(const std::string &filePath);

    std::vector<std::vector<float>> LOWER_DIAG_ROW(const std::string &filePath);
};
#endif //PEA_ANNEALING_WORKONFILES_H
