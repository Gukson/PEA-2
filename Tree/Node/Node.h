//
// Created by Kuba on 04/10/2024.
//

#ifndef PEA_NODE_H
#define PEA_NODE_H

#include <iostream>
#include <vector>

using namespace std;
class Node {
public:
    int get_value();
    vector<pair<Node*,int>> getVectorOfNodes();
    void addNodeToVector(Node *n, int v);


    void set_value(int v);
    explicit Node(int val){
        value = val;
        vectorOfNodes = vector<pair<Node*,int>>();
    }

private:
    vector<pair<Node*,int>> vectorOfNodes;
    int value;
};


#endif //PEA_NODE_H
