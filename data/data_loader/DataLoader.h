//
// Created by Kuba on 04/10/2024.
//

#ifndef PEA_DATALOADER_H
#define PEA_DATALOADER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "../../Tree/Node/Node.h"

using namespace std;

class DataLoader {
public:
    vector<Node> loadData(string fileName);
    int optimum;
};


#endif //PEA_DATALOADER_H
