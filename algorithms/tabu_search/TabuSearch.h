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
#include "../../config/configClass/Config.h"
#include <vector>

using namespace std;

class TabuSearch : public AlgoFrame {
public:
    vector<int> best_way;
    int cost;
    int iterations;
    int tabu_size = 0;
    void algorithm(vector<Node> nodes) override;
    void test_algorithm(vector<Node> nodes) override;
    vector<tuple<vector<int>, int, pair<int, int>>> candidates;

private:
    ValueCalculator v;  // Zmienna v (ValueCalculator)
    vector<int> twoOptSwap(vector<int>& route, int i, int k);
};



#endif //PEA_2_TABUSEARCH_H
