//
// Created by Kuba on 15/12/2024.
//

#ifndef PEA_2_ANTCOLONYOPTIMIZATION_H
#define PEA_2_ANTCOLONYOPTIMIZATION_H

#include <iostream>
#include "../AlgoFrame.h"
#include "../pomocnicze/ant/Ant.h"
#include "../pomocnicze/valueCalculator/ValueCalculator.h"
#include "../../config/configClass/Config.h"

using namespace std;

class AntColonyOptimization : public AlgoFrame {
public:
    float alfa = 3;
    float beta = 1;
    float rho = 0.5;
    float q = 100.0; //początkowa wartośc feromonu
    int m; //ilość mrówek
    int iterations; //ilość iteracji
    vector<vector<double>> feromon;
    vector<int> best_way = vector<int>();
    int best_cost;
    ValueCalculator v = ValueCalculator();


    void algorithm(vector<Node> nodes) override;
    void test_algorithm(vector<Node> nodes) override;

private:
    vector<Ant> ant_vector;
};


#endif //PEA_2_ANTCOLONYOPTIMIZATION_H
