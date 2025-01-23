//
// Created by Kuba on 02/01/2025.
//

#include "Tester.h"
#include "../data/data_loader/DataLoader.h"
#include "../config/configClass/Config.h"
#include "../algorithms/SimulatedAnnealing/SimulatedAnnealing.h"
#include "../algorithms/AntColony/AntColonyOptimization.h"
#include "../algorithms/Tabu_search/TabuSearch.h"

void Tester::tester() {
    Config c = Config();
    c.loadConfig("config.json");
    for (int index = 0; index < c.files.size(); index++) {
        DataLoader dataLoader = DataLoader();
        string p = c.files[index];
        vector<Node> nodes = dataLoader.loadData(p);
        ofstream outputFile;
        outputFile.open("../data/output/" + c.outputFile, std::ios_base::app);
        outputFile << c.files[index] << ";" << endl;
        outputFile.close();

        for (auto i : std::vector<std::string>{"nn", "random"}) {
            for (auto k : std::vector<std::string>{"swap", "change"}) {
                c.TabuUpperLimit = i;
                c.Tabuchange_way_by = k;
                TabuSearch t = TabuSearch(c, dataLoader.optimum);
                t.test_algorithm(nodes);
            }
        }

        float tab[3] = {0.995, 0.99, 0.999};
        string tab1[2] = {"swap","change"};
        string tab21[2]={"nn","random"};

        for (auto z: tab21) {
            for(auto i: tab){
                for(auto k:tab1){
                    c.way = k;
                    c.coolingType = "geo";
                    c.annealingAlfa = i;
                    c.SAUpperLimit = z;
                    SimulatedAnnealing s = SimulatedAnnealing(c,dataLoader.optimum);
                    s.test_algorithm(nodes);
                }
            }
        }

        float tab2[3] = {15,20,30};
        for(auto z:tab21) {
            for(auto i: tab2){
                for(auto k:tab1) {
                    c.coolingType = "log";
                    c.temperature = i;
                    c.SAUpperLimit = z;
                    SimulatedAnnealing s = SimulatedAnnealing(c,dataLoader.optimum);
                    s.test_algorithm(nodes);
                }
            }
        }

        string tab3[2] = {"QAS", "CAS"};
        float tab4[3] = {1.0,2.0,5.0};
        int tab5[3] = {1,3,5};
        int tab6[3] = {3,5,7};
        for(auto i: tab3){
            for(auto j: tab4){
                for(auto k: tab5){
                    for(auto m: tab6){
                        c.AntAlfa = k;
                        c.AntBeta = m;
                        c.initialAmountOfPheromone = j;
                        c.PheromoneUpdateMethod = i;
                        c.numberOfAnts = nodes.size();
                        AntColonyOptimization ant = AntColonyOptimization(c, dataLoader.optimum);
                        ant.test_algorithm(nodes);
                    }
                }
            }
        }
    }
}
