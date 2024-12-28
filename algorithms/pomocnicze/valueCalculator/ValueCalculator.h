//
// Created by Kuba on 12/12/2024.
//

#ifndef PEA_2_VALUECALCULATOR_H
#define PEA_2_VALUECALCULATOR_H

#include <vector>
#include "../../../Tree/Node/Node.h"
#include "algorithm"
using namespace std;

class ValueCalculator {
public:
    pair<Node*, int> findNeighbor(Node *node,int targetValue);
    int calculate_value(vector<Node> nodes, vector<int> way);
};


#endif //PEA_2_VALUECALCULATOR_H
