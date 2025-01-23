//
// Created by Kuba on 28/12/2024.
//

#ifndef PEA_2_SIMULATEDANNEALING_H
#define PEA_2_SIMULATEDANNEALING_H

#include "../AlgoFrame.h"
#include "../pomocnicze/valueCalculator/ValueCalculator.h"
#include "../NearestNeighbour/NearestNeighbour.h"
#include "../../config/configClass/Config.h"
#include "../pomocnicze/statCalculator/statCalculator.h"
#include "../pomocnicze/usun_wpolne/usunWspolne.h"
#include <vector>
#include <random>
#include <cmath>
#include <chrono>
class SimulatedAnnealing : public AlgoFrame  {
public:
    SimulatedAnnealing(Config c, int opt){
        config = c;
        this->alfa = c.annealingAlfa;
        this->temperature = c.temperature;
        this->start_temperature = c.temperature;
        this->min_temperature = c.min_temperature;
        this->choose_way_by = c.way;
        this->optimum = opt;
        this->C = config.SAc;

    }

    void algorithm(vector<Node> nodes) override;
    void test_algorithm(vector<Node> nodes) override;
private:
    Config config;
    ValueCalculator v = ValueCalculator();
    int cost = 0;
    chrono::duration<double, std::milli> ms_double;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;
    vector<int> best_way;
    int lb;
    int optimum;
    float alfa;
    float start_temperature;
    float temperature;
    float min_temperature;
    string choose_way_by;
    bool overTime = false;

    int noChangesStreak = 0;
    int last_cost;
    float C;

private:
    vector<int> swap_random_cities(vector<int> actual_order);
    vector<int> change_order(vector<int> actual_order);
    vector<int> GenerateRandomWay(vector<Node> nodes);

};


#endif //PEA_2_SIMULATEDANNEALING_H
