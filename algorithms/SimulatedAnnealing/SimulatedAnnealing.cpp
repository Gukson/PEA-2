//
// Created by Kuba on 28/12/2024.
//

#include "SimulatedAnnealing.h"

void SimulatedAnnealing::algorithm(vector<Node> nodes) {
    while(temperature > min_temperature){
        vector<int> new_way = vector<int>();
        if(this->choose_way_by == "change") new_way = change_order(best_way);
        else new_way = swap_random_cities(best_way);

        int new_cost = v.calculate_value(nodes,new_way);
        int delta = new_cost - cost;
        if (delta < 0 || (exp(-1.0 * delta / temperature) > ((double)rand() / RAND_MAX))) {
            if(new_cost < cost){
                cost = new_cost;
                best_way = new_way;
                //zatrzymujemy algorytm, gdy znajdziemy wartość optymalną
                if (cost == optimum) break;
            }
        }
        temperature *= alfa;
    }
}

void SimulatedAnnealing::test_algorithm(vector<Node> nodes) {
    vector<Node*> visited = vector<Node*>();
    NearestNeighbour n = NearestNeighbour();
    vector<double> timeMeasurements = vector<double>();
    vector<double> absolutes = vector<double>();
    vector<double> relatives = vector<double>();

    for(int x = 0; x < config.repetitionsPerInstance; x++){

        n.nearestNeighbour(&nodes[0], nodes.size(),visited,0,&nodes[0],1);
        best_way = n.best_way; //to jest nasze początkowe minimum lokalne
        cost = n.result;
        auto start = chrono::high_resolution_clock::now();
        algorithm(nodes);
        auto finish = chrono::high_resolution_clock::now();
        ms_double = finish - start;
        timeMeasurements.push_back(ms_double.count() / 1000);

    }
    statCalculator s = statCalculator();
    vector<double> stats = s.calcStats(timeMeasurements,absolutes,relatives);
    s.statsOutput(stats,timeMeasurements,absolutes,relatives,best_way,cost,config.showInConsole,optimum,config.outputFile);

}

vector<int> SimulatedAnnealing::swap_random_cities(vector<int> actual_order) {
    actual_order.pop_back();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, actual_order.size()-1);
    int first = dist(gen);
    int second = dist(gen);
    while(second == first){
        second = dist(gen);
    }
    swap(actual_order[first],actual_order[second]);
    actual_order.push_back(actual_order[0]);
    return actual_order;
}

vector<int> SimulatedAnnealing::change_order(vector<int> actual_order) {
    actual_order.pop_back();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, actual_order.size()-1);
    int length_swap = dist(gen);

    uniform_int_distribution<> egh(0,actual_order.size()-1-length_swap);
    int start_swap = egh(gen);

    reverse(actual_order.begin()+ start_swap,actual_order.begin()+start_swap+length_swap);
    actual_order.push_back(actual_order[0]);
    return actual_order;
}