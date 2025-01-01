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
#include "../pomocnicze/statCalculator/statCalculator.h"
#include <random>
#include <chrono>
using namespace std;

class AntColonyOptimization : public AlgoFrame {
public:
    AntColonyOptimization(Config c, int opt){
        this->config = c;
        this->alfa = config.AntAlfa;
        this->beta = config.AntBeta;
        this->rho = config.AntRho;
        this->q = config.initialAmountOfPheromone;
        this->m = config.numberOfAnts;
        this->optimum = opt;
    }




    void algorithm(vector<Node> nodes) override;
    void test_algorithm(vector<Node> nodes) override;

private:
    vector<Ant> ant_vector;
    Config config;
    float alfa;
    float beta;
    float rho;
    float q; //poczatkowa ilosc feromonu
    int m; //ilość mrówek
    int optimum;
    vector<int> best_way = vector<int>();
    int best_cost = INT16_MAX;
    vector<vector<double>> feromon;
    ValueCalculator v = ValueCalculator();

    chrono::duration<double, std::milli> ms_double;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;

    int noChangesStreak = 0;
    int last_cost = INT16_MAX;
};


#endif //PEA_2_ANTCOLONYOPTIMIZATION_H
