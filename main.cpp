#include <iostream>
#include <vector>
#include <fstream> //do plików
#include "data/data_loader/DataLoader.h"
#include "algorithms/tabu_search/TabuSearch.h"
#include "algorithms/AlgoFrame.h"
using namespace std;
int main() {

    DataLoader dataLoader = DataLoader();
    vector<Node> nodes = dataLoader.loadData("11nodes.txt");
    TabuSearch t;

    // Wywołanie metody test_algorithm
    t.test_algorithm(nodes);

}
