cmake_minimum_required(VERSION 3.24)
project(PEA_annealing)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_annealing main.cpp Utilities/WorkOnFiles.cpp Utilities/WorkOnFiles.h Algorithm/SimulatedAnnealing.cpp Algorithm/SimulatedAnnealing.h
        Algorithm/Parameters/Temperature.cpp
        Algorithm/Parameters/Temperature.h
        Algorithm/Parameters/Solution.cpp
        Algorithm/Parameters/Solution.h
        Algorithm/Parameters/Neighborhood.cpp
        Algorithm/Parameters/Neighborhood.h
        Utilities/Test.cpp
        Utilities/Test.h)
