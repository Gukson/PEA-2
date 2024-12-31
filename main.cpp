#include <iostream>
#include <vector>
#include <fstream> //do plików
#include "data/data_loader/DataLoader.h"
#include "algorithms/tabu_search/TabuSearch.h"
#include "algorithms/AlgoFrame.h"
#include "algorithms/AntColony/AntColonyOptimization.h"
#include "algorithms/SimulatedAnnealing/SimulatedAnnealing.h"
using namespace std;
int main() {

    DataLoader dataLoader = DataLoader();

    vector<Node> nodes = dataLoader.loadData("13nodes.txt");
    Config c = Config();
    c.loadConfig("config.json");
//    TabuSearch t;
//
//    // Wywołanie metody test_algorithm
//    t.test_algorithm(nodes);

//    AntColonyOptimization ant = AntColonyOptimization();
//    ant.m = 20;
//    ant.iterations = 100;
//    ant.algorithm(nodes);

    SimulatedAnnealing s = SimulatedAnnealing(c,dataLoader.optimum);
    s.test_algorithm(nodes);

}
