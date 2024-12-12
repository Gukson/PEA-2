//
// Created by Kuba on 04/10/2024.
//

#include "DataLoader.h"

vector<string> split_sentence(string sen) {

    stringstream ss(sen);

    string word;

    vector<string> words;

    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

vector<Node> DataLoader::loadData(string fileName) {
    ifstream file;
    file.open("../data/data_files/" + fileName);
    if (file.is_open()){
        cout << "Otworzono plik z danymi" << endl;
    }
    string line;
    getline(file,line);
    int nodesAmount = stoi(line);
    getline(file,line);
    optimum = stoi(line);
    vector<Node> nodes = vector<Node>();

    for(int x = 0; x < nodesAmount; x++){
        nodes.push_back(Node(x));
    }

    int lineIndex = 0;
    while(getline(file,line)){
        vector<string> numbers = split_sentence(line);
        for(int x = 0 ; x< nodesAmount; x++){
            string s = numbers[x];
            if(stoi(s) != -1){
                // Dodaj połączenie z lineIndex do x
                nodes[lineIndex].addNodeToVector(&(nodes[x]), stoi(s));

                // Dodaj odwrotne połączenie, z x do lineIndex (dwukierunkowe)
//                nodes[x].addNodeToVector(&(nodes[lineIndex]), stoi(s));
            }
        }
        lineIndex++;
    }
    return nodes;
}
