//
// Created by Kuba on 28/12/2024.
//

#include "SimulatedAnnealing.h"

void SimulatedAnnealing::algorithm(vector<Node> nodes) {
    int k = 0;
    while(temperature > min_temperature){
        k++;
        vector<int> new_way = vector<int>();
        if(this->choose_way_by == "change") new_way = change_order(best_way);
        else new_way = swap_random_cities(best_way);

        int new_cost = v.calculate_value(nodes,new_way);
        int delta = new_cost - cost;
        if (delta < 0 || (exp(-1.0 * delta / temperature) > ((double)rand() / RAND_MAX))) {

            //przekroczenie limitu czasu
            if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - time).count() >=
                config.maxTime) {
                this->overTime = true;
                throw std::runtime_error("przekroczono limit czasowy");
            }

            //zatrzymujemy algorytm, gdy znajdziemy wartość optymalną
            if (new_cost == optimum) {
                cost = new_cost;
                best_way = new_way;
                throw std::runtime_error("znaleziono optimum");
            }

            if(new_cost - optimum <= (lb * config.SAAcceptableDeviationFromOptimum)/100.0) {
                cost = new_cost;
                best_way = new_way;
                throw std::runtime_error("Wynik w granicach tolerancji odchylenia od wyniku optymalnego");
            }

            if(new_cost < cost){
                cost = new_cost;
                best_way = new_way;
            }
            if(new_cost > cost){
                this->noChangesStreak += 1;
            } else{
                this->noChangesStreak = 0;
            }
            this->last_cost = new_cost;

            //powtórzenia bez zmian
            if(this->noChangesStreak == config.SAIterationsLimit){
                throw std::runtime_error("osiągnięto limit pomiarów bez zmiany wyniku");
            }
        }
        if(config.coolingType == "geo"){
            temperature *= alfa;
        } else{
            temperature = start_temperature / log(1+k);
        }
    }
}

void SimulatedAnnealing::test_algorithm(vector<Node> nodes) {
    vector<Node*> visited = vector<Node*>();
    NearestNeighbour n = NearestNeighbour();
    vector<double> timeMeasurements = vector<double>();
    vector<double> absolutes = vector<double>();
    vector<double> relatives = vector<double>();
    vector<int> results = vector<int>();

    for(int x = 0; x < config.repetitionsPerInstance; x++){

        auto start = chrono::high_resolution_clock::now();
        time = start;
        n.time = start;
        try {
            if (config.SAUpperLimit == "nn") {n.nearestNeighbour(&nodes[0], nodes.size(),visited,0,&nodes[0],1);
                best_way = n.best_way; //to jest nasze początkowe minimum lokalne
                cost = n.result;}
            else {
                best_way = GenerateRandomWay(nodes);
                cost = v.calculate_value(nodes,best_way);
            }

            last_cost = cost;
            lb = primAlgorithm(nodes);
            algorithm(nodes);
        } catch (const std::runtime_error &e) {
            std::cerr << "Błąd: " << e.what() << std::endl;
        }

        auto finish = chrono::high_resolution_clock::now();
        ms_double = finish - start;
        timeMeasurements.push_back(ms_double.count() / 1000);
        results.push_back(cost);
        if(this->overTime)break;
    }

    int temp = 0;
    for (auto x : results) {
        temp += x;
    }
    temp /= results.size();
    statCalculator s = statCalculator();
    vector<double> stats = s.calcStats(timeMeasurements,absolutes,relatives);
    string info = config.coolingType + " : " +
                     (config.coolingType == "geo" ? std::to_string(alfa) : std::to_string(C)) +
                     " way: " + choose_way_by + " upperLimit: " + config.SAUpperLimit;
    s.statsOutput(stats,timeMeasurements,absolutes,relatives,best_way,temp,config.showInConsole,optimum,config.outputFile, "SimulatedAnnealing", info);

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


vector<int> SimulatedAnnealing::GenerateRandomWay(vector<Node> nodes){
    random_device rd; // Źródło entropii
    mt19937 gen(rd()); // Mersenne Twister z ziarna rd()
    vector<int> nodes_int = vector<int>();
    for(auto p: nodes){
        nodes_int.push_back(p.get_value());
    }

    shuffle(nodes_int.begin(), nodes_int.end(), gen);
    nodes_int.push_back(nodes_int[0]);

    return nodes_int;
}