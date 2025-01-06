//
// Created by Kuba on 12/12/2024.
//

#include "TabuSearch.h"

void TabuSearch::algorithm(vector<Node> nodes) {
    FixedSizeQueue<pair<int,int>> tabu_queue = FixedSizeQueue<pair<int,int>>(tabu_size);
    while(true){
        //zatrzymanie, jeżeli znaleziono wartość optymalną
        if(this->cost == optimum){
            throw std::runtime_error("znaleziono optimum");
        }

        candidates.clear();
        //generowanie i sprawdzanie sąsiedztw
        //chcmey generować pary sąsiedztwa bez powtórzeń - tzn. uznajemy przypadek [1,2] i [2,1] za równoważne
        //WAŻNE - j zawsze mniejsze od k
        for (int j = 1; j < best_way.size()-1; ++j) {
            for (int k = j + 1; k < best_way.size()-1; ++k) {
                vector<int> newRoute = twoOptSwap(best_way, j, k);
                newRoute[newRoute.size()-1] = newRoute[0];
                int value = v.calculate_value(nodes,newRoute);
                bool isInTabu = tabu_queue.contains(make_pair(j,k));

                if(!isInTabu || value > cost){
                    candidates.push_back(make_tuple(newRoute,value, make_pair(j,k)));
                }


                //sprawdzanie, czy nie przekroczono czasu
                if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - time).count() >=
                    config.maxTime) {
                    this->overTime = true;
                    throw std::runtime_error("przekroczono limit czasowy");
                }
            }
        }

        //sortujemy listę kandydatów
        std::sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) {
            return get<1>(a) < get<1>(b);
        });
        tabu_queue.push(get<2>(candidates[0]));

        if(get<1>(candidates[0]) - optimum <= (optimum*config.TabuAcceptableDeviationFromOptimum)/100){
            this->best_way = get<0>(candidates[0]);
            this->cost = get<1>(candidates[0]);
            throw std::runtime_error("Wynik w granicach tolerancji odchylenia od wyniku optymalnego");
        }

        if(get<1>(candidates[0]) < this->cost){
            this->best_way = get<0>(candidates[0]);
            this->cost = get<1>(candidates[0]);
        }
        else if(get<1>(candidates[0]) == last_cost){
            this->noChangesStreak += 1;
        } else{
            this->noChangesStreak = 0;
        }
        this->last_cost = get<1>(candidates[0]);

        //powtórzenia bez zmian
        if(this->noChangesStreak == config.TabuIterationsLimit){
            throw std::runtime_error("osiągnięto limit pomiarów bez zmiany wyniku");
        }

    }
}

void TabuSearch::test_algorithm(vector<Node> nodes) {
    vector<Node*> visited = vector<Node*>();



    cout << "poszedł algos" << endl;

    //założenia dla długości listy Tabu:
    //Dla N < 50 -> N*0.2
    //Dla N < 50 <= 500 -> N * 0.05
    //Dla N > 500 -> N * 0.01

    if(nodes.size() < 50) {tabu_size = nodes.size() * 0.5;}
    else if(nodes.size() > 50 && nodes.size() < 500) {tabu_size = nodes.size() * 0.05;}
    else {tabu_size = nodes.size() * 0.01;}
    this->last_cost = cost;

    vector<double> timeMeasurements = vector<double>();
    vector<double> absolutes = vector<double>();
    vector<double> relatives = vector<double>();

    for(int x = 0; x < config.repetitionsPerInstance; x++){
        auto start = chrono::high_resolution_clock::now();
        time = start;
        try {
            if(config.TabuUpperLimit == "nn"){
                NearestNeighbour n = NearestNeighbour();
                n.time = start;
                n.nearestNeighbour(&nodes[0], nodes.size(),visited,0,&nodes[0],1);
                best_way = n.best_way; //to jest nasze początkowe minimum lokalne
                cost = n.result;
            } else{
                best_way = GenerateRandomWay(nodes);
                cost = v.calculate_value(nodes,best_way);
            }
            algorithm(nodes);
        } catch (const std::runtime_error &e) {
            std::cerr << "Błąd: " << e.what() << std::endl;
        }

        auto finish = chrono::high_resolution_clock::now();
        ms_double = finish - start;
        timeMeasurements.push_back(ms_double.count() / 1000);
        if(this->overTime)break;
    }

    statCalculator s = statCalculator();
    vector<double> stats = s.calcStats(timeMeasurements,absolutes,relatives);
    ofstream outputFile;
    outputFile.open("../data/output/" + config.outputFile, std::ios_base::app);
    outputFile << config.TabuUpperLimit << endl;
    s.statsOutput(stats,timeMeasurements,absolutes,relatives,best_way,cost,config.showInConsole,optimum,config.outputFile, "TabuSearch");
}

vector<int> TabuSearch::twoOptSwap(vector<int>& route, int i, int k) {
    std::vector<int> newRoute(route); // Kopia obecnej trasy

    std::reverse(newRoute.begin() + i, newRoute.begin() + k + 1);

    return newRoute;
}

vector<int> TabuSearch::GenerateRandomWay(vector<Node> nodes){
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