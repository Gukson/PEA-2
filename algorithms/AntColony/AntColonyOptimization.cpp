//
// Created by Kuba on 15/12/2024.
//

#include "AntColonyOptimization.h"


void AntColonyOptimization::test_algorithm(vector<Node> nodes) {
    vector<double> timeMeasurements = vector<double>();
    vector<double> absolutes = vector<double>();
    vector<double> relatives = vector<double>();
    vector<int> results = vector<int>();

    for(int x = 0; x < config.repetitionsPerInstance; x++){
        this->best_way.clear();
        this->best_cost = INT32_MAX;
        this->feromon = std::vector<std::vector<double>>(nodes.size(), std::vector<double>(nodes.size(), 1));
        this->ant_vector = vector<Ant>();
        this->noChangesStreak = 0;
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
            lb = primAlgorithm(nodes);
            algorithm(nodes);
        } catch (const std::runtime_error &e) {
            std::cerr << "Błąd: " << e.what() << std::endl;
        }

        auto finish = chrono::high_resolution_clock::now();
        ms_double = finish - start;
        timeMeasurements.push_back(ms_double.count() / 1000);
        results.push_back(best_cost);
        if (this->overTime) break;
    }

    int temp = 0;
    for (auto x : results) {
        temp += x;
    }
    temp /= results.size();


    statCalculator s = statCalculator();
    vector<double> stats = s.calcStats(timeMeasurements,absolutes,relatives);
    string info = config.PheromoneUpdateMethod +
                     " : alfa - " + std::to_string(config.AntAlfa) +
                     " : Beta - " + std::to_string(config.AntBeta) +
                     " : Q - " + std::to_string(q);
    s.statsOutput(stats,timeMeasurements,absolutes,relatives,best_way,temp,config.showInConsole,optimum,config.outputFile, "Ant", info);
}

void AntColonyOptimization::algorithm(vector<Node> nodes) {
    vector<vector<double>> matrix(nodes.size(), vector<double>(nodes.size(), 0));
    int iteration = 0;

    while (true) {
        // Resetowanie mrówek
        for (int x = 0; x < this->m; x++) {
            ant_vector[x].reset(nodes[x % nodes.size()]); // Rotacja zamiast losowania
        }
        int new_cost = 0;
        // Iteracja dla każdej mrówki
        for (auto& a : ant_vector) {
            a.time = this->time;

            try {
                a.make_tour(nodes, this->feromon, this->alfa, this->beta, config.PheromoneUpdateMethod, this->q);
            } catch (const std::runtime_error& e) {
                this->overTime = true;
                throw std::runtime_error("przekroczono limit czasowy");
            }

            // Sprawdzanie najlepszej trasy
            new_cost = a.tourLength;

            if (new_cost < best_cost) {
                best_cost = new_cost;
                best_way = a.getTourValues();
            }

            // Warunek: znalezienie wyniku optymalnego
            if (new_cost == optimum) {
                best_cost = new_cost;
                best_way = a.getTourValues();
                throw std::runtime_error("Znaleziono optimum");
            }

            // Warunek: wynik w granicach tolerancji od wyniku optymalnego
            if (new_cost - optimum <= (lb * config.AntAcceptableDeviationFromOptimum) / 100) {
                best_way = a.getTourValues();
                best_cost = new_cost;
                throw std::runtime_error("Wynik w granicach tolerancji odchylenia od wyniku optymalnego");
            }


            // Aktualizacja feromonów w metodzie CAS
            if (config.PheromoneUpdateMethod == "CAS") {
                for (int i = 0; i < a.tour.size() - 1; i++) {
                    int from = a.tour[i]->get_value();
                    int to = a.tour[i + 1]->get_value();
                    matrix[from][to] += this->q / a.tourLength;
                }
            }
        }
        // Sprawdzanie powtórzeń bez zmian
        if (new_cost >= best_cost) {
            this->noChangesStreak += 1;
        } else {
            this->noChangesStreak = 0;
        }

        // Warunek: osiągnięcie limitu iteracji bez poprawy wyniku
        if (this->noChangesStreak >= config.TabuIterationsLimit) {
            throw std::runtime_error("osiągnięto limit pomiarów bez zmiany wyniku");
        }


        iteration++;

        // Parowanie i aktualizacja feromonów
        for (int z = 0; z < feromon.size(); z++) {
            for (int y = 0; y < feromon[z].size(); y++) {
                feromon[z][y] *= (1 - this->rho);
                if (feromon[z][y] < 1e-6) feromon[z][y] = 1e-6;

                if (config.PheromoneUpdateMethod == "CAS") {
                    feromon[z][y] += matrix[z][y];
                }
            }
        }

        if (config.PheromoneUpdateMethod == "CAS") {
            for (auto& row : matrix) {
                fill(row.begin(), row.end(), 0.0);
            }
        }

        // Warunek: przekroczenie limitu czasu
        if (std::chrono::duration_cast<std::chrono::minutes>(
                std::chrono::high_resolution_clock::now() - time).count() >= config.maxTime) {
            this->overTime = true;
            throw std::runtime_error("przekroczono limit czasowy");
        }


    }
}