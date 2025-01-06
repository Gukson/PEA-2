//
// Created by Kuba on 12/12/2024.
//

#ifndef PEA_2_TABUSEARCH_H
#define PEA_2_TABUSEARCH_H

#include <iostream>
#include "../AlgoFrame.h"
#include "../pomocnicze/valueCalculator/ValueCalculator.h"
#include "../NearestNeighbour/NearestNeighbour.h"
#include "../pomocnicze/FixedSizeQueue.h"
#include "../pomocnicze/statCalculator/statCalculator.h"
#include "../../config/configClass/Config.h"
#include <vector>
#include <random>
#include <chrono>

using namespace std;

class TabuSearch : public AlgoFrame {
public:
    TabuSearch(Config c, int opt){
        this->config = c;
        this->optimum = opt;
    }
    vector<int> best_way;

    void algorithm(vector<Node> nodes) override;
    void test_algorithm(vector<Node> nodes) override;
    vector<tuple<vector<int>, int, pair<int, int>>> candidates;

private:
    ValueCalculator v;  // Zmienna v (ValueCalculator)
    vector<int> twoOptSwap(vector<int>& route, int i, int k);
    vector<int> GenerateRandomWay(vector<Node> nodes);

    chrono::duration<double, std::milli> ms_double;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;

    Config config;
    int cost;
    int tabu_size = 0;
    int noChangesStreak = 0;
    int last_cost;
    int optimum;
    bool overTime = false;
};



#endif //PEA_2_TABUSEARCH_H
