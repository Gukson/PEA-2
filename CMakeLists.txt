cmake_minimum_required(VERSION 3.28)
project(PEA_2)

set(CMAKE_CXX_STANDARD 17)

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
        data/data_loader/DataLoader.cpp)
