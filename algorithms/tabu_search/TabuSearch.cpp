//
// Created by Kuba on 12/12/2024.
//

#include "TabuSearch.h"

void TabuSearch::algorithm(vector<Node> nodes) {
    FixedSizeQueue<pair<int,int>> tabu_queue = FixedSizeQueue<pair<int,int>>(tabu_size);
    for(int i = 0; i < iterations; i++){
        candidates.clear();
        //generowanie i sprawdzanie sąsiedztw
        //chcmey generować pary sąsiedztwa bez powtórzeń - tzn. uznajemy przypadek [1,2] i [2,1] za równoważne
        //WAŻNE - j zawsze mniejsze od k
        for (int j = 1; j < best_way.size()-1; ++j) {
            for (int k = j + 1; k < best_way.size()-1; ++k) {
                vector<int> newRoute = twoOptSwap(best_way, i, k);
                newRoute[newRoute.size()-1] = newRoute[0];
                int value = v.calculate_value(nodes,newRoute);
                bool isInTabu = tabu_queue.contains(make_pair(j,k));

                if(!isInTabu || value > cost){
                    candidates.push_back(make_tuple(newRoute,value, make_pair(j,k)));
                }
            }
        }

        //sortujemy listę kandydatów
        std::sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) {
            return get<1>(a) < get<1>(b);
        });

        this->best_way = get<0>(candidates[0]);
        this->cost = get<1>(candidates[0]);
        tabu_queue.push(get<2>(candidates[0]));
        cout << i << " <- ";
        for(int x : best_way){
            cout << x << " ";
        }
        cout << " : " << cost << endl;

    }
}

void TabuSearch::test_algorithm(vector<Node> nodes) {
    vector<Node*> visited = vector<Node*>();
    NearestNeighbour n = NearestNeighbour();
    n.nearestNeighbour(&nodes[0], nodes.size(),visited,0,&nodes[0],1);
    best_way = n.best_way; //to jest nasze początkowe minimum lokalne
    cost = n.result;
    iterations = nodes.size()*nodes.size();

    //założenia dla długości listy Tabu:
    //Dla N < 50 -> N*0.2
    //Dla N < 50 <= 500 -> N * 0.05
    //Dla N > 500 -> N * 0.01

    if(nodes.size() < 50) {tabu_size = nodes.size() * 0.5;}
    else if(nodes.size() > 50 && nodes.size() < 500) {tabu_size = nodes.size() * 0.05;}
    else {tabu_size = nodes.size() * 0.01;}

    //ustawienie rozmiaru kolejki tabu

    this->algorithm(nodes);
}

vector<int> TabuSearch::twoOptSwap(vector<int>& route, int i, int k) {
    std::vector<int> newRoute(route); // Kopia obecnej trasy

    std::reverse(newRoute.begin() + i, newRoute.begin() + k + 1);

    return newRoute;
}


