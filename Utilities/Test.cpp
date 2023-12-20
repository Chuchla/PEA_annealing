//
// Created by chuchla on 19.12.23.
//

#include "Test.h"
#include "WorkOnFiles.h"
#include "../Algorithm/SimulatedAnnealing.h"
#include <vector>
#include <tuple>
#include <sys/resource.h>
#include <chrono>
#include <iostream>

void Test::TestSimulatedAnnealing(const std::string &filePath){
    std::vector<std::tuple<std::string, int, float>>  ini = WorkOnFiles::ReadFromIni(filePath);
    std::vector<std::tuple<std::string,float,long long, long long, int, float, float>> toCsv;

    std::string outputName{get<0>(ini[ini.size()-1])};
    std::string fileName{};
    float avgCost{};
    long long avgTime{};
    long long avgMemory{};
    int verteciesNumber{};
    float optimalCost{};
    float error{};
    std::tuple<std::string,float,long long, long long, int, float, float> tupleToCsv{};

    struct rusage usage;

    long long beforeMemory = usage.ru_maxrss;
    long long afterMemory = usage.ru_maxrss;
    long long workMemory{};
    auto beforeTime = std::chrono::high_resolution_clock::now();
    auto afterTime = std::chrono::high_resolution_clock::now();
    auto workTime = std::chrono::duration_cast<std::chrono::milliseconds>(afterTime - beforeTime).count();

    vector<long long> timeVector;
    vector<float> costVector;
    vector<long long> memoryVector;

    for(int i = 0; i < ini.size()-1; i++){
        for(int j = 0 ; j < get<1>(ini[i]); j++){

            getrusage(RUSAGE_SELF, &usage);
            beforeMemory = usage.ru_maxrss;
            beforeTime = std::chrono::high_resolution_clock::now();
            auto retVec = SimulatedAnnealing::RunSimulatedAnnealing(get<0>(ini[i]));
            afterTime = std::chrono::high_resolution_clock::now();
            getrusage(RUSAGE_SELF, &usage);
            afterMemory = usage.ru_maxrss;

            workTime = std::chrono::duration_cast<std::chrono::milliseconds>(afterTime - beforeTime).count();
            std::cout << get<0>(ini[i]) << " czas: " <<  workTime << "[ms]" << std::endl;
            workMemory = afterMemory - beforeMemory;


            timeVector.push_back(workTime);
            memoryVector.push_back(workMemory);
            costVector.push_back(get<3>(retVec[retVec.size()-1]));//ostatnia dystans z retVec
            verteciesNumber = get<4>(retVec[0]).size();
            WorkOnFiles::WriteToCSV(get<0>(ini[i]), retVec);
        }
        for(int j = 0; j < timeVector.size(); j++){
            avgTime+= timeVector[j];
            avgCost+= costVector[j];
            avgMemory+= memoryVector[j];
        }
        fileName = get<0>(ini[i]);
        avgCost/= timeVector.size();
        avgTime/= timeVector.size();
        avgMemory/= timeVector.size();
        optimalCost = get<2>(ini[i]);
        error = ((avgCost-optimalCost)/optimalCost)*100;
        tupleToCsv = {fileName,avgCost,avgTime,avgMemory,verteciesNumber,optimalCost,error};
        toCsv.push_back(tupleToCsv);

        avgTime = 0;
        avgCost = 0;
        avgMemory = 0;
        error = 0;
        timeVector.clear();
        costVector.clear();
        memoryVector.clear();
    }
    WorkOnFiles::WriteTestToCSV(outputName, toCsv);

}