//
// Created by GS65 on 14.11.2023.
//
#include <algorithm>
#include "WorkOnFiles.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>

//ATT, GEO

std::vector<std::tuple<std::string, int, float>> WorkOnFiles::ReadFromIni(const std::string &filePath){
    std::fstream file(filePath);
    std::vector<std::tuple<std::string, int ,float>> data;
    std::string line;
    if(file.is_open()){
        while(std::getline(file, line)){
            std::stringstream iss(line);
            std::string name{};
            int repetitions{};
            float distance{};
            iss >> name;
            iss >> repetitions;
            iss >> distance;

            data.push_back({name,repetitions,distance});

        }
    }
    return data;
}
void WorkOnFiles::WriteToCSV(const std::string& fileName,std::vector<std::tuple<int, long long, float, float, std::vector<int>>> data){
    std::string fileCsv = fileName.substr(0,fileName.find_last_of('.'));
    fileCsv = fileCsv + ".csv";
    std::ofstream file(fileCsv);

    if(file.is_open()){
        file << "Numer epoki,Czas[ms],Temp,Dystans,Sciezka\n";

        for(const auto& element : data ){
            file << std::get<0>(element) << ",";
            file << std::get<1>(element) << ",";
            file << std::get<2>(element) << ",";
            file << std::get<3>(element) << ",<";

            for(const auto& vertex : std::get<4>(element)){
                file << vertex << " ";
            }
            file << ">\n";
        }
    }
    file.close();
}
void WorkOnFiles::WriteTestToCSV(const std::string& outputName, std::vector<std::tuple<std::string,float,long long, long long, int, float, float>> data){
    std::ofstream file(outputName);
    if(file.is_open()){
        file<<"Nazwa instancji,Sredni koszt najlepszych rozwiazan,Sredni czas[ms],Srednie zuzycie pamieci,Rozmiar instancji,Optymalny koszt,Procent bledu\n";

        for(const auto& element : data){
            file << std::get<0>(element) << ",";
            file << std::get<1>(element) << ",";
            file << std::get<2>(element) << ",";
            file << std::get<3>(element) << ",";
            file << std::get<4>(element) << ",";
            file << std::get<5>(element) << ",";
            file << std::get<6>(element) << ",";
            file << "\n";
        }
    }
    file.close();
}



std::vector<std::vector<float>> WorkOnFiles::GetGraph(const std::string &filePath){
    auto dotPosition = filePath.rfind('.');
    std::string extension{};
    if(dotPosition != std::string::npos){
        extension = filePath.substr(dotPosition + 1);
    } else{
        throw std::runtime_error("Nie podano rozszerzenia pliku");
    }

    if(extension == "txt") return GetGraphFromTXTFile(filePath);
    else if(extension == "tsp" or extension == "atsp") return GetGraphFromTSPFile(filePath);
    else throw std::runtime_error("Nie obslugiwany format pliku zrodlowego");

}
std::vector<std::vector<float>> WorkOnFiles::GetGraphFromTXTFile(const std::string &filePath){
    std::ifstream file(filePath);
    std::string line;
    getline(file,line);
    int numberOfVertices{};
    std::istringstream iss(line);
    iss >> numberOfVertices;
    std::vector<std::vector<float>> graph(numberOfVertices, std::vector<float>(numberOfVertices, 0));
    int row{};
    while(std::getline(file,line)){
        std::istringstream iss(line);
        for(int i = 0; i < numberOfVertices; i++){
            if(i != row) iss >> graph[row][i];
            else{
                iss >> graph[row][i];
                graph[row][i] = std::numeric_limits<float>::infinity();
            }
        }
        row++;
    }

    return graph;
}

std::vector<std::vector<float>> WorkOnFiles::FullMatrix(const std::string &filePath) {
    std::ifstream file(filePath);
    std::string line;
    bool startReading{};
    int numberOfVertecies{};
    std::vector<std::vector<float>> graph;
    std::vector<float> row;
    while (std::getline(file, line)) {
        if (line.find("DIMENSION: ") != std::string::npos) {
            auto found = line.find("DIMENSION:");
            std::istringstream iss(line.substr(found + 10));
            iss >> numberOfVertecies;
            std::cout << numberOfVertecies << std::endl;
            continue;
        }
        if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos) {
            startReading = true;
            continue;
        }
        if (startReading and
            ((line.find("EOS")) != std::string::npos or (line.find("DISPLAY_DATA_SECTION")) != std::string::npos)) {
            break;
        }
        if (startReading) {
            std::istringstream iss(line);
            float weight;
            while (iss >> weight) {
                //New row
                if (weight > 9001) weight = std::numeric_limits<float>::infinity();
                if (row.size() == numberOfVertecies) {
                    graph.push_back(row);
                    row.erase(row.begin(), row.end());
                    row.push_back(weight);
                } else {
                    row.push_back(weight);
                }
            }
        }
    }
    graph.push_back(row);
    return graph;
}

std::vector<std::vector<float>> WorkOnFiles::LOWER_DIAG_ROW(const std::string &filePath) {
    std::ifstream file;
    file.open(filePath);
    int numberOfVertecies{};
    std::vector<float> lowerDiagRow;
    std::string line;
    bool startReading{};
    if (!file.is_open()) {
        throw std::runtime_error("Nie udało się otworzyć pliku");
    }
    while (std::getline(file, line)) {
        if (line.find("DIMENSION:") != std::string::npos) {
            auto found = line.find("DIMENSION: ");
            std::istringstream iss(line.substr(found + 10));
            iss >> numberOfVertecies;
            std::cout << numberOfVertecies << std::endl;
            continue;
        }
        if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos) {
            startReading = true;
            continue;
        }
        if (startReading) {
            std::istringstream iss(line);
            float weight{};
            while (iss >> weight) {
                lowerDiagRow.push_back(weight);
            }
        }
    }
    std::vector<std::vector<float>> graph(numberOfVertecies, std::vector<float>(numberOfVertecies, 0));
    int k{};
    int row{};
    int j{};
    while (row < numberOfVertecies) {
        if (lowerDiagRow[k] == 0) {
            graph[row][j] = lowerDiagRow[k];
            row++;
            k++;
            j = 0;
            continue;
        }
        graph[row][j] = lowerDiagRow[k];
        k++;
        j++;
    }
    for (int i = 0; i < numberOfVertecies; i++) {
        for (int x = 0; x < numberOfVertecies; x++) {
            if (i != x) graph[i][x] = graph[x][i];
        }
    }
    for (int i = 0; i < numberOfVertecies; i++) {
        graph[i][i] = std::numeric_limits<float>::infinity();
    }
    return graph;
}

std::vector<std::vector<float>> WorkOnFiles::EUC2D(const std::string &filePath) {
    std::vector<std::pair<float, float>> coordinates;
    std::ifstream file;
    file.open(filePath);
    int numberOfVertecies{};
    std::string line;
    bool startReading{};
    if (!file.is_open()) throw std::runtime_error("Nie można otworzyć plików");
    while (std::getline(file, line)) {
        if (line.find("DIMENSION: ") != std::string::npos) {
            auto found = line.find("DIMENSION: ");
            std::istringstream iss(line.substr(found + 10));
            iss >> numberOfVertecies;
            std::cout << numberOfVertecies << std::endl;
            continue;
        }
        if (line.find("NODE_COORD_SECTION") != std::string::npos) {
            startReading = true;
            continue;
        }
        if (startReading) {
            std::istringstream iss(line);
            float x{}, y{};
            float index{};
            iss >> index >> x >> y;
            coordinates.emplace_back(x, y);
        }
        if (coordinates.size() >= numberOfVertecies and numberOfVertecies != 0) {
            break;
        }
    }


    std::vector<std::vector<float>> graph(numberOfVertecies, std::vector<float>(numberOfVertecies, 0));
    for (int i = 0; i < coordinates.size(); i++) {
        for (int j = 0; j < coordinates.size(); j++) {
            if (i != j) {
                float dx = coordinates[j].first - coordinates[i].first;
                float dy = coordinates[j].second - coordinates[i].second;
                graph[i][j] = std::sqrt(dx * dx + dy * dy);
            } else graph[i][j] = std::numeric_limits<float>::infinity();
        }
    }

    return graph;
}


std::vector<std::vector<float>> WorkOnFiles::GetGraphFromTSPFile(const std::string &filePath) {
    std::ifstream file(filePath);
    std::string line;
    std::string edgeWeightType;
    std::string edgeWeightFormat;
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku");
    }
    while (std::getline(file, line)) {
        if (line.find("EDGE_WEIGHT_TYPE:") != std::string::npos) {
            auto found = line.find("EDGE_WEIGHT_TYPE:");
            std::istringstream iss(line.substr(found + 17));
            iss >> edgeWeightType;
        }
        if (line.find("EDGE_WEIGHT_FORMAT:") != std::string::npos) {
            auto found = line.find("EDGE_WEIGHT_FORMAT:");
            std::istringstream iss(line.substr((found + 19)));
            iss >> edgeWeightFormat;
            break;
        }
    }
    if (edgeWeightType == "EXPLICIT" and edgeWeightFormat == "FULL_MATRIX") {
        return FullMatrix(filePath);
    } else if (edgeWeightType == "EUC_2D") {
        return EUC2D(filePath);
    } else if (edgeWeightType == "EXPLICIT" and edgeWeightFormat == "LOWER_DIAG_ROW") {
        return LOWER_DIAG_ROW(filePath);
    }
    throw std::runtime_error("Nie obsługiwany format reprezentacji grafu");
}


