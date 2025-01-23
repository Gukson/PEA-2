//
// Created by Kuba on 07/10/2024.
//

#include "Config.h"


void Config::openJSON(string filename) {
    ifstream jsonFile;
    jsonFile.open("../config/configFiles/"+filename);

    if(jsonFile.is_open()){
        data = json::parse(jsonFile);
    }

}

void Config::loadConfig(string fileName) {
    openJSON(fileName);

    for(int x = 0; x < data["files"].size(); x++){
        files.push_back(data["files"][x]["file_name"]);
    }
    maxTime = data["max_time"];
    repetitionsPerInstance = data["repetitions_per_instance"];
    outputFile = data["output_file"];
    progressBar = data["progress_bar"];
    showNodesInConsole = data["show_nodes_in_console"];
    showInConsole = data["measurement_results_in_the_console"];
    AntColony = data["algorithms"]["AntColony"];
    SimulatedAnnealing = data["algorithms"]["SimulatedAnnealing"];
    TabuSearch = data["algorithms"]["TabuSearch"];


    //SA
    annealingAlfa = data["SimulatedAnnealing"]["alfa"];
    temperature =  data["SimulatedAnnealing"]["start_temperature"];
    min_temperature = data["SimulatedAnnealing"]["min_temperature"];
    way = data["SimulatedAnnealing"]["choose_way_by"];
    SAIterationsLimit = data["SimulatedAnnealing"]["FinishAfterIterationsWithNoChanges"];
    SAAcceptableDeviationFromOptimum = data["SimulatedAnnealing"]["AcceptableDeviationFromOptimum"];
    coolingType = data["SimulatedAnnealing"]["coolingType"];
    SAc = data["SimulatedAnnealing"]["C"];
    SAUpperLimit = data["SimulatedAnnealing"]["UpperLimit"];

    //Tabu
    TabuUpperLimit = data["TabuSearch"]["UpperLimit"];
    TabuIterationsLimit = data["TabuSearch"]["FinishAfterIterationsWithNoChanges"];
    TabuAcceptableDeviationFromOptimum = data["TabuSearch"]["AcceptableDeviationFromOptimum"];
    Tabuchange_way_by = data["TabuSearch"]["choose_way_by"];

    //Ant
    PheromoneUpdateMethod = data["AntColonyOptimization"]["PheromoneUpdateMethod"];
    AntAlfa = data["AntColonyOptimization"]["Alfa"];
    AntBeta = data["AntColonyOptimization"]["Beta"];
    AntRho = data["AntColonyOptimization"]["Rho"];
    numberOfAnts = data["AntColonyOptimization"]["NumberOfAnts"];
    initialAmountOfPheromone = data["AntColonyOptimization"]["InitialAmountOfPheromone"];
    AntAcceptableDeviationFromOptimum = data["AntColonyOptimization"]["AcceptableDeviationFromOptimum"];
}

