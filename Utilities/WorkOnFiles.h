//
// Created by GS65 on 14.11.2023.
//

#ifndef PEA_ANNEALING_WORKONFILES_H
#define PEA_ANNEALING_WORKONFILES_H

#include <vector>
#include <string>
class WorkOnFiles{
public:

    static std::vector<std::vector<float>> GetGraph(const std::string &filePath);
    static void
    WriteToCSV(const std::string &fileName,
               std::vector<std::tuple<int, long long int, float, float, std::vector<int>>>);

    static std::vector<std::tuple<std::string, int, float>> ReadFromIni(const std::string &filepath);

    static void WriteTestToCSV(const std::string &outputName,
                        std::vector<std::tuple<std::string, float, long long int, long long int, int, float, float>> data);

private:

    static std::vector<std::vector<float>> GetGraphFromTSPFile(const std::string& filePath);

    static std::vector<std::vector<float>> GetGraphFromTXTFile(const std::string& filePath);


    static std::vector<std::vector<float>> FullMatrix(const std::string &filePath);

    static std::vector<std::vector<float>> EUC2D(const std::string &filePath);

    static std::vector<std::vector<float>> LOWER_DIAG_ROW(const std::string &filePath);
};
#endif //PEA_ANNEALING_WORKONFILES_H
