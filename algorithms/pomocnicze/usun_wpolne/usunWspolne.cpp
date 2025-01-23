//
// Created by Kuba on 14/11/2024.
//

#include "usunWspolne.h"

void usunWspolne(vector<pair<Node*,int>>& A, vector<Node*>& B) {
    unordered_set<int> values;
    for(const auto& p: B){
        values.insert(p->get_value());
    }
    A.erase(remove_if(A.begin(), A.end(),
                      [&values](const pair<Node*,int>& p) {
                          return p.first && values.count(p.first->get_value()) > 0;
                      }),
            A.end());
}

int primAlgorithm(vector<Node>& graph) {
    if (graph.empty()) return 0;

    // Inicjalizacja
    vector<bool> inMST(graph.size(), false);  // Czy wierzchołek jest w MST
    priority_queue<pair<int, pair<Node*, Node*>>, vector<pair<int, pair<Node*, Node*>>>, greater<>> pq;
    vector<pair<Node*, Node*>> mstEdges;
    int totalCost = 0;

    // Dodanie krawędzi wychodzących z pierwszego wierzchołka
    Node startNode = graph[0];
    inMST[0] = true;

    for (auto& edge : startNode.getVectorOfNodes()) {
        pq.push({edge.second, {&startNode, edge.first}});
    }

    // Iteracja po wierzchołkach
    while (!pq.empty() && mstEdges.size() < graph.size() - 1) {
        auto [weight, edge] = pq.top();
        pq.pop();

        Node* fromNode = edge.first;
        Node* toNode = edge.second;

        // Jeśli wierzchołek docelowy jest już w MST, pomijamy
        int toIndex = toNode->get_value(); // Zakładamy, że `get_value()` zwraca unikalny indeks wierzchołka
        if (inMST[toIndex]) continue;

        // Dodajemy wierzchołek i krawędź do MST
        inMST[toIndex] = true;
        mstEdges.push_back({fromNode, toNode});
        totalCost += weight; // Dodajemy wagę do całkowitego kosztu

        // Dodanie nowych krawędzi wychodzących z nowego wierzchołka
        for (auto& edge : toNode->getVectorOfNodes()) {
            if (!inMST[edge.first->get_value()]) {
                pq.push({edge.second, {toNode, edge.first}});
            }
        }
    }

    return totalCost;
}