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

    //SA
    annealingAlfa = data["SimulatedAnnealingSettings"]["alfa"];
    temperature =  data["SimulatedAnnealingSettings"]["start_temperature"];
    min_temperature = data["SimulatedAnnealingSettings"]["min_temperature"];
    way = data["SimulatedAnnealingSettings"]["choose_way_by"];
    SAIterationsLimit = data["SimulatedAnnealingSettings"]["SAFinishAfterIterationsWithNoChanges"];
    SAAcceptableDeviationFromOptimum = data["SimulatedAnnealingSettings"]["SAAcceptableDeviationFromOptimum"];

    //Tabu
    TabuUpperLimit = data["TabuSearch"]["TabuUpperLimit"];
    TabuIterationsLimit = data["TabuSearch"]["TabuFinishAfterIterationsWithNoChanges"];
    TabuAcceptableDeviationFromOptimum = data["TabuSearch"]["TabuAcceptableDeviationFromOptimum"];

}

