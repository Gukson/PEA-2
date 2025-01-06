#include <iostream>
#include <vector>
#include <fstream> //do plików
#include "data/data_loader/DataLoader.h"
#include "algorithms/tabu_search/TabuSearch.h"
#include "algorithms/AlgoFrame.h"
#include "algorithms/AntColony/AntColonyOptimization.h"
#include "algorithms/SimulatedAnnealing/SimulatedAnnealing.h"
#include "tester/Tester.h"
using namespace std;

int main() {
    Tester t = Tester();
    t.tester();
//    DataLoader dataLoader = DataLoader();
//
//    vector<Node> nodes = dataLoader.loadData("7nodes.txt");
//    Config c = Config();
//    c.loadConfig("config.json");

//    TabuSearch t = TabuSearch(c, dataLoader.optimum);
//    t.test_algorithm(nodes);
//
//    AntColonyOptimization ant = AntColonyOptimization(c, dataLoader.optimum);
//    ant.test_algorithm(nodes);
//
//    SimulatedAnnealing s = SimulatedAnnealing(c,dataLoader.optimum);
//    s.test_algorithm(nodes);

}
