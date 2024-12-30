//
// Created by Kuba on 15/12/2024.
//

#include "AntColonyOptimization.h"

void AntColonyOptimization::test_algorithm(vector<Node> nodes) {
    vector<vector<double>> matrix(nodes.size(), vector<double>(nodes.size(),0));

    for(int x = 0; x < iterations; x++) {
        for(int x = 0; x < this->m; x++){
            int randomNumber = rand() % (nodes.size());
            ant_vector[x].reset(nodes[randomNumber]);
        }

        //mrówka robi trasę
        for (auto a: ant_vector) {
            a.make_tour(nodes, this->feromon, this->alfa, this->beta);
            for (int i = 0; i < a.tour.size() - 2; i++) {
                matrix[a.tour[i]->get_value()][a.tour[i + 1]->get_value()] += this->q / a.tourLength;
            }
        }

        for (int z = 0; z < feromon.size(); z++) {
            for (int y = 0; y < feromon[z].size(); y++) {
                feromon[z][y] = (1 - this->rho) * feromon[z][y];
                if(feromon[z][y] <= 0){
                    feromon[z][y] = 1e-6;
                }
                feromon[z][y] += matrix[z][y];
            }
        }
        for (auto& row : matrix) {
            fill(row.begin(), row.end(), 0.0);
        }

        //wyświtlanie wyniku po iteracji
        vector<int> way = vector<int>();
        vector<bool> visited(nodes.size(), false);
        visited[0] = true;
        way.push_back(0);
        while (way.size() < nodes.size()){
            int current_node = way[way.size()-1];
            int z = -1;
            double y = 0;
            for(int p = 0; p < nodes.size(); p++){
                if(p != current_node and !visited[p]){
                    if(feromon[current_node][p] > y){
                        z = p;
                        y = feromon[current_node][p];
                    }
                }
            }
            way.push_back(z);
            visited[z] = true;
        }
        way.push_back(0);
        for(auto p: way) cout << p << " ";
        cout << " : " << v.calculate_value(nodes,way) << endl;
    }
}

void AntColonyOptimization::algorithm(vector<Node> nodes) {
    this->ant_vector = vector<Ant>();
    srand(time(nullptr));
    for(int x = 0; x < this->m; x++){
        int randomNumber = rand() % (nodes.size());
        ant_vector.push_back(Ant(&nodes[randomNumber]));
    }
    this->feromon = std::vector<std::vector<double>>(nodes.size(), std::vector<double>(nodes.size(), 1e-6));
    this->test_algorithm(nodes);
}
