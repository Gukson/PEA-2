//
// Created by Kuba on 12/12/2024.
//

#include "ValueCalculator.h"

pair<Node*, int> ValueCalculator::findNeighbor(Node* node, int targetValue) {
    // Uzyskaj referencję do vectorOfNodes dla uniknięcia kopiowania
    const auto& neighbors = node->getVectorOfNodes();
    for (const auto& neighbor : neighbors) {
        if (neighbor.first->get_value() == targetValue) {
            return neighbor;
        }
    }
    return {nullptr, -1}; // Brak sąsiada
}

int ValueCalculator::calculate_value(vector<Node> nodes, vector<int> way) {
    if (way.size() < 2) {
        throw std::invalid_argument("'way' must contain at least 2 elements");
    }

    int value = 0;

    for (int x = 0; x < way.size() - 1; x++) {
        if (way[x] < 0 || way[x] >= nodes.size()) {
            throw std::out_of_range("Invalid index in 'way'");
        }

        const auto& vectorOfNodes = nodes[way[x]].getVectorOfNodes();
        for (const auto& neighbor : vectorOfNodes) {
            if (neighbor.first == nullptr) {
                throw std::runtime_error("Invalid Node* in vectorOfNodes");
            }

            if (neighbor.first->get_value() == way[x + 1]) {
                value += neighbor.second;
            }
        }
    }

    return value;
}