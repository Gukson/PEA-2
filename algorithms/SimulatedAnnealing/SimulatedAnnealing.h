//
// Created by Kuba on 28/12/2024.
//

#ifndef PEA_2_SIMULATEDANNEALING_H
#define PEA_2_SIMULATEDANNEALING_H

#include "../AlgoFrame.h"
#include "../pomocnicze/valueCalculator/ValueCalculator.h"
#include "../NearestNeighbour/NearestNeighbour.h"
#include <vector>
#include <random>
class SimulatedAnnealing : public AlgoFrame  {
public:
    float alfa = 0.995;
    float temperature = 100;
    float min_temperature = 0;
    int cost;
    ValueCalculator v = ValueCalculator();
    vector<int> best_way;
    void algorithm(vector<Node> nodes) override;
    void test_algorithm(vector<Node> nodes) override;

private:
    vector<int> swap_random_cities(vector<int> actual_order);
    vector<int> change_order(vector<int> actual_order);

};


#endif //PEA_2_SIMULATEDANNEALING_H
