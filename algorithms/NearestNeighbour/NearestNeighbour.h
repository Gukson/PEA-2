//
// Created by Kuba on 06/10/2024.
//

#ifndef PEA_NEARESTNEIGHBOUR_H
#define PEA_NEARESTNEIGHBOUR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../Tree/Node/Node.h"
#include "../pomocnicze/usun_wpolne/usunWspolne.h"

using namespace std;

class NearestNeighbour {
public:
    int result = INT_MAX;

    vector<int> best_way = vector<int>();
    void nearestNeighbour(Node *start, int size, vector<Node*> visited, int actualCost,Node *con,int c);
    void findBestWay(vector<Node> nodes);
};


#endif //PEA_NEARESTNEIGHBOUR_H
