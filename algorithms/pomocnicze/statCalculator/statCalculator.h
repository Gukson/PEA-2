//
// Created by Kuba on 31/12/2024.
//

#ifndef PEA_2_STATCALCULATOR_H
#define PEA_2_STATCALCULATOR_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class statCalculator {
public:
    void statsOutput(vector<double> stats, vector<double> timeMeasurements, vector<double> absolutes,
                                     vector<double> relatives, vector<int> best_way, int wynik, bool show, int bestWynik,
                                     string filename, string algos,string istotne);
    vector<double> calcStats(vector<double> time, vector<double>& absolute, vector<double>& relative);
};


#endif //PEA_2_STATCALCULATOR_H
