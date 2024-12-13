//
// Created by Kuba on 12/12/2024.
//

#include "ValueCalculator.h"

pair<Node*, int> ValueCalculator::findNeighbor(Node *node,int targetValue) {
    for(int x = 0; x < node->getVectorOfNodes().size(); x++){
        if(node->getVectorOfNodes()[x].first->get_value() == targetValue){
            return node->getVectorOfNodes()[x];
        }
    }
    return {nullptr, -1}; // Brak sąsiada
}

int ValueCalculator::calculate_value(vector<Node> nodes, vector<int> way) {
    int sum = 0;
    for(int x = 0; x<way.size()-1; x++){
        pair<Node*, int> temp = findNeighbor(&nodes[way[x]],way[x+1]);
        if (temp.first != nullptr){
            sum += temp.second;
        }
    }
    return sum;
}
