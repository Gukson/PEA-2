#include <iostream>
#include <vector>
#include <fstream> //do plików
#include "data/data_loader/DataLoader.h"
#include "algorithms/tabu_search/TabuSearch.h"
#include "algorithms/AlgoFrame.h"

#include "algorithms/AntColony/AntColonyOptimization.h"
#include "algorithms/SimulatedAnnealing/SimulatedAnnealing.h"
#include "algorithms/pomocnicze/usun_wpolne/usunWspolne.h"
#include "tester/Tester.h"
using namespace std;

int main() {

    DataLoader dataLoader = DataLoader();

    Config c = Config();
    c.loadConfig("config.json");

    for (auto file : c.files) {
        vector<Node> nodes = dataLoader.loadData(file);
        if (c.TabuSearch) {
            TabuSearch t = TabuSearch(c, dataLoader.optimum);
            t.test_algorithm(nodes);
        }

        AntColonyOptimization ant = AntColonyOptimization(c, dataLoader.optimum);
        ant.test_algorithm(nodes);
        if (c.AntColony) {
            AntColonyOptimization ant = AntColonyOptimization(c, dataLoader.optimum);
            ant.test_algorithm(nodes);
        }

        if (c.SimulatedAnnealing) {
            SimulatedAnnealing s = SimulatedAnnealing(c,dataLoader.optimum);
            s.test_algorithm(nodes);
        }
    }

}
