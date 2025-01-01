//
// Created by Kuba on 15/12/2024.
//

#ifndef PEA_2_ANT_H
#define PEA_2_ANT_H

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "../../../Tree/Node/Node.h"
#include "../../pomocnicze/usun_wpolne/usunWspolne.h"
using namespace std;

class Ant {
public:
    vector<Node *> tour;
    Node *startNode;
    int tourLength;

    // Konstruktor:
    Ant(Node *start) {
        startNode = start;
        tour.push_back(start);
    }

    // Resetowanie stanu mrówki:
    void reset(Node startCity) {
        this->tour.clear();       // Czyszczenie trasy
        this->tour.push_back(startNode); // Dodanie węzła startowego
        this->tourLength = 0;     // Zresetowanie długości trasy

    };

    void make_tour(vector<Node> nodes, vector<vector<double>>& feromon, float alfa, float beta, string method, float q);
};


#endif //PEA_2_ANT_H
