//
// Created by Kuba on 15/12/2024.
//

#include "Ant.h"

void Ant::make_tour(vector<Node> nodes, vector<vector<double>>& feromon, float alfa, float beta, string method, float q) {
    this->tourLength = 0;
    while (true) {
        Node* current_Node = tour.back();
        vector<pair<Node*, int>> nodes_temp = current_Node->getVectorOfNodes();
        usunWspolne(nodes_temp, tour);

        if (nodes_temp.empty()) break;

        double sum = 0.0;
        vector<double> probabilities(nodes_temp.size());
        for (size_t i = 0; i < nodes_temp.size(); i++) {
            double pheromoneValue = feromon[current_Node->get_value()][nodes_temp[i].first->get_value()];
            pheromoneValue = std::max(pheromoneValue, 1e-6);

            double n_i = 1.0 / nodes_temp[i].second;
            probabilities[i] = pow(pheromoneValue, alfa) * pow(n_i, beta);
            sum += probabilities[i];
        }

        if (sum == 0.0) throw std::runtime_error("Sum of probabilities is zero.");

        for (size_t i = 1; i < probabilities.size(); i++) {
            probabilities[i] += probabilities[i - 1];
        }
        std::random_device rd;        // Źródło entropii
        std::mt19937 gen(rd());       // Generator Mersenne Twister
        std::uniform_real_distribution<> dist(0.0, probabilities.back());
        double randValue = dist(gen);

        for (size_t i = 0; i < probabilities.size(); i++) {
            if (randValue <= probabilities[i]) {
                Node* next_Node = nodes_temp[i].first;
                tour.push_back(next_Node);
                tourLength += nodes_temp[i].second;

                // DAS: Aktualizacja feromonu na podstawie odległości
                if (method == "DAS") {
                    feromon[current_Node->get_value()][next_Node->get_value()] += q / double(nodes_temp[i].second);
                }

                // QAS: Aktualizacja feromonu na podstawie całkowitej długości trasy
                if (method == "QAS") {
                    feromon[current_Node->get_value()][next_Node->get_value()] += q / double(tourLength);
                }

                break;
            }
        }
    }

    // Dodanie ostatniej krawędzi do zamknięcia trasy (powrót do początkowego węzła)
    Node* current_Node = &nodes[tour.back()->get_value()];
    for (auto n : current_Node->getVectorOfNodes()) {
        if (n.first->get_value() == this->tour[0]->get_value()) {
            this->tour.push_back(tour[0]);
            this->tourLength += n.second;
        }
    }
}
