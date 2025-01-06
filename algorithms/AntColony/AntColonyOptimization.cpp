//
// Created by Kuba on 15/12/2024.
//

#include "AntColonyOptimization.h"


void AntColonyOptimization::test_algorithm(vector<Node> nodes) {
    vector<double> timeMeasurements = vector<double>();
    vector<double> absolutes = vector<double>();
    vector<double> relatives = vector<double>();

    for(int x = 0; x < config.repetitionsPerInstance; x++){
        this->best_way.clear();
        this->best_cost = INT16_MAX;
        this->feromon = std::vector<std::vector<double>>(nodes.size(), std::vector<double>(nodes.size(), 1));
        this->ant_vector = vector<Ant>();
        std::random_device rd;        // Źródło entropii
        std::mt19937 gen(rd());       // Generator Mersenne Twister
        std::uniform_int_distribution<> dist(0, nodes.size()-1);
        for(int x = 0; x < this->m; x++){
            int randomNumber = dist(gen);
            ant_vector.push_back(Ant(&nodes[randomNumber],config.maxTime));
        }
        auto start = chrono::high_resolution_clock::now();
        time = start;
        try {
            algorithm(nodes);
        } catch (const std::runtime_error &e) {
            std::cerr << "Błąd: " << e.what() << std::endl;
        }

        auto finish = chrono::high_resolution_clock::now();
        ms_double = finish - start;
        timeMeasurements.push_back(ms_double.count() / 1000);
        if (this->overTime) break;
    }


    statCalculator s = statCalculator();
    vector<double> stats = s.calcStats(timeMeasurements,absolutes,relatives);
    ofstream outputFile;
    outputFile.open("../data/output/" + config.outputFile, std::ios_base::app);
    outputFile << config.PheromoneUpdateMethod << " : alfa -  " << config.AntAlfa << " : Beta -" << config.AntBeta << " : Q - " << q << endl;
    s.statsOutput(stats,timeMeasurements,absolutes,relatives,best_way,best_cost,config.showInConsole,optimum,config.outputFile, "Ant");
}

void AntColonyOptimization::algorithm(vector<Node> nodes) {
    vector<vector<double>> matrix(nodes.size(), vector<double>(nodes.size(),0));

    while (true) {
        std::random_device rd;        // Źródło entropii
        std::mt19937 gen(rd());       // Generator Mersenne Twister
        std::uniform_int_distribution<> dist(0, nodes.size()-1);
        for(int x = 0; x < this->m; x++){
            int randomNumber = dist(gen);
            ant_vector[x].reset(nodes[randomNumber]);
        }

        //mrówka robi trasę
        for (auto a: ant_vector) {
            try {
                a.time = this->time;
                a.make_tour(nodes, this->feromon, this->alfa, this->beta, config.PheromoneUpdateMethod, this->q);
            } catch (const std::runtime_error &e) {
                this->overTime = true;
                throw std::runtime_error("przekroczono limit czasowy");
            }

            vector<int> way = vector<int>();

            for(auto p: a.tour) way.push_back(p->get_value());

            int new_cost = a.tourLength;

            if(new_cost < best_cost){
                best_cost = new_cost;
                best_way = way;
            }

            if(new_cost == optimum){
                best_cost = new_cost;
                best_way = way;
                throw std::runtime_error("Znaleziono optimum");
            }

            if(new_cost - optimum <= (optimum * config.AntAcceptableDeviationFromOptimum)/100){
                best_way = way;
                best_cost = new_cost;
                throw std::runtime_error("Wynik w granicach tolerancji odchylenia od wyniku optymalnego");
            }

            if(new_cost == last_cost){
                this->noChangesStreak += 1;
            } else{
                this->noChangesStreak = 0;
            }
            this->last_cost = new_cost;

            //powtórzenia bez zmian
            if(this->noChangesStreak == config.TabuIterationsLimit){
                throw std::runtime_error("osiągnięto limit pomiarów bez zmiany wyniku");
            }

            if(config.PheromoneUpdateMethod == "CAS"){
                for (int i = 0; i < a.tour.size() - 2; i++) {
                    matrix[a.tour[i]->get_value()][a.tour[i + 1]->get_value()] += this->q / a.tourLength;
                }
            }

            if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - time).count() >=
                config.maxTime) {
                this->overTime = true;
                throw std::runtime_error("przekroczono limit czasowy");
            }
        }

        //parowanie feromonu
        for (int z = 0; z < feromon.size(); z++) {
            for (int y = 0; y < feromon[z].size(); y++) {
                feromon[z][y] = (1 - this->rho) * feromon[z][y];
                if(feromon[z][y] <= 0){
                    feromon[z][y] = 1e-6;
                }
                if(config.PheromoneUpdateMethod == "CAS"){
                    feromon[z][y] += matrix[z][y];
                }
            }
        }

        for (auto& row : matrix) {
            fill(row.begin(), row.end(), 0.0);
        }

    }
}
