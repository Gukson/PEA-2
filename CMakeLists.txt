cmake_minimum_required(VERSION 3.28)
project(PEA_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(PEA_2 main.cpp
        algorithms/pomocnicze/valueCalculator/ValueCalculator.cpp
        algorithms/pomocnicze/valueCalculator/ValueCalculator.h
        algorithms/AlgoFrame.h
        algorithms/AlgoFrame.h
        algorithms/tabu_search/TabuSearch.cpp
        algorithms/tabu_search/TabuSearch.h
        algorithms/NearestNeighbour/NearestNeighbour.cpp
        algorithms/pomocnicze/usun_wpolne/usunWspolne.cpp
        Tree/Node/Node.cpp
        algorithms/pomocnicze/FixedSizeQueue.h
        data/data_loader/DataLoader.cpp
        algorithms/AntColony/AntColonyOptimization.cpp
        algorithms/AntColony/AntColonyOptimization.h
        algorithms/pomocnicze/ant/Ant.cpp
        algorithms/pomocnicze/ant/Ant.h)
