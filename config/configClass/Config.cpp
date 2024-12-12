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
    bruteForce = data["algorithms"]["Bruteforce"];
    nn = data["algorithms"]["Nearest-neighbour"];
    radnom = data["algorithms"]["Random"];
    dfs = data["algorithms"]["DFS"];
    bfs = data["algorithms"]["BFS"];
    lcfs = data["algorithms"]["LCFS"];
    showInConsole = data["measurement_results_in_the_console"];
}

