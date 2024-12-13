//
// Created by Kuba on 12/12/2024.
//

#ifndef PEA_2_ALGOFRAME_H
#define PEA_2_ALGOFRAME_H

#include <iostream>
#include "../Tree/Node/Node.h"

using namespace std;

class AlgoFrame {
public:
    virtual ~AlgoFrame() = default;
    virtual void algorithm(vector<Node> nodes) = 0;
    virtual void test_algorithm(vector<Node> nodes) = 0;
};


#endif //PEA_2_ALGOFRAME_H
