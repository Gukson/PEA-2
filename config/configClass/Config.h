//
// Created by Kuba on 07/10/2024.
//

#ifndef PEA_CONFIG_H
#define PEA_CONFIG_H

#include <iostream>
#include <fstream>
#include <vector>
#include "../../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;



using namespace std;
class Config {
public:
    vector<string> files;
    string outputFile;
    void loadConfig(string fileName);
    int maxTime;
    bool progressBar;
    bool showInConsole;
    bool showNodesInConsole;
    int repetitionsPerInstance;

    //algorithm
    bool AntColony;
    bool SimulatedAnnealing;
    bool TabuSearch;

    //SimulatedAnnealing
    float annealingAlfa;
    float temperature;
    float min_temperature;
    string way;
    int SAIterationsLimit;
    int SAAcceptableDeviationFromOptimum;

    //Tabu
    string TabuUpperLimit;
    int TabuIterationsLimit;
    int TabuAcceptableDeviationFromOptimum;




private:
    void openJSON(string fileName);
    json data;


};


#endif //PEA_CONFIG_H
