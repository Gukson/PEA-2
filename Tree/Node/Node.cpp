//
// Created by Kuba on 04/10/2024.
//

#include "Node.h"

int Node::get_value(){
    return value;
}

vector<pair<Node*, int>> Node::getVectorOfNodes() {
    return vectorOfNodes;
}

void Node::set_value(int v) {
    value = v;
}

void Node::addNodeToVector(Node* n, int v) {
    vectorOfNodes.push_back(make_pair(n,v));
}



