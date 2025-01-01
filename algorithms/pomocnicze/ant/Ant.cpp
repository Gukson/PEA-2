//
// Created by Kuba on 15/12/2024.
//

#include "Ant.h"


void Ant::make_tour(vector<Node> nodes, vector<vector<double>>& feromon, float alfa, float beta, string method, float q) {
    this->tourLength = 0;
    while(true) {
        Node *current_Node = tour[tour.size() - 1];
//        cout << current_Node->get_value() << " " << endl;
        vector<pair<Node *, int>> nodes_temp = current_Node->getVectorOfNodes();
        usunWspolne(nodes_temp, tour);
//        for(auto p: nodes_temp) cout << p.first->get_value() << " ";
//        cout << endl;
//        cout << "rozmiar wspolnych : " << nodes_temp.size() << endl;
        if(nodes_temp.empty()) {
//            cerr << "No nodes to process after removing visited nodes." << endl;
            break;
        }
        double sum = 0.0;
        vector<pair<Node *, double>> p = vector<pair<Node *, double>>();
        for (auto n : nodes_temp) {
            double n_i = 1.0 / n.second;  // n.second to odległość
            double pheromoneValue = feromon[current_Node->get_value()][n.first->get_value()];

            if (pheromoneValue <= 0.0) {  // Upewnij się, że feromony są dodatnie
                pheromoneValue = 1e-6;  // Minimalny feromon
            }

            double temp = pow(pheromoneValue, alfa) * pow(n_i, beta);
            p.emplace_back(n.first, temp);
            sum += temp;
        }

        // Jeśli suma nadal wynosi zero, wymuś minimalną wartość
        if (sum == 0.0) {
            cerr << "Error: Sum of probabilities is zero. Setting minimal value for probabilities." << endl;
            sum = 1e-6;  // Minimalna wartość, aby uniknąć dzielenia przez zero
        }
        double suma = 0.0;
        for(auto & o : p){
            o.second = o.second/sum;
            suma += o.second;
            o.second = suma;
//            cout << o.first->get_value() << " : " << o.second << endl;
        }


        //Wybieranie trasy na podsatwei prawdopodobieństwa
        random_device rd; // Źródło entropii
        mt19937 gen(rd()); // Generator liczb losowych
        uniform_real_distribution<> dist(0.0, 1.0); // Rozkład jednostajny
        double losowaLiczba = dist(gen);
//        cout << "random: " << losowaLiczba << endl;
        for(auto & o : p){
//            cout << o.second << endl;
            if(losowaLiczba < o.second){
//                cout << "wybrano liczbe: " << o.first->get_value() << endl;
                this->tour.push_back(o.first);
                for(auto i: current_Node->getVectorOfNodes()){
                    if(i.first->get_value() == o.first->get_value()){
                        this->tourLength += i.second;
                        if(method == "DAS"){
                            feromon[current_Node->get_value()][o.first->get_value()] += q/float(i.second);
                        }
                        break;
                    }
                }

                if(method == "QAS"){
                    feromon[current_Node->get_value()][o.first->get_value()] += q/float(tourLength);
                }

                break;
            }
        }
    }
    Node current_Node = nodes[tour[tour.size()-1]->get_value()];
    for(auto n: current_Node.getVectorOfNodes()){
        if(n.first->get_value() == this->tour[0]->get_value()){
            this->tour.push_back(tour[0]);
            this->tourLength += n.second;
        }
    }
}


