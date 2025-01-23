//
// Created by Kuba on 12/12/2024.
//

#include "TabuSearch.h"

void TabuSearch::algorithm(vector<Node> nodes) {
    FixedSizeQueue<pair<int, int>> tabu_queue(tabu_size);
    int minDiversityThreshold = 3; // Minimalny próg różnorodności (liczba różnych krawędzi)

    while (true) {
        // Sprawdzenie, czy znaleziono wartość optymalną
        if (this->cost == optimum) {
            throw std::runtime_error("Znaleziono optimum");
        }

        candidates.clear();

        for (int j = 1; j < best_way.size() - 1; ++j) {
            for (int k = j + 1; k < best_way.size() - 1; ++k) {
                vector<int> newRoute;

                if (config.Tabuchange_way_by == "change") {
                    newRoute = twoOptSwap(best_way, j, k);
                } else if (config.Tabuchange_way_by == "swap") {
                    std::vector<int> temp(best_way); // Kopia obecnej trasy
                    std::swap(temp[j], temp[k]);
                    newRoute = temp;
                }

                int value = v.calculate_value(nodes, newRoute);
                bool isInTabu = tabu_queue.contains(make_pair(j, k));


                if(!isInTabu || value > cost){
                    candidates.push_back(make_tuple(newRoute,value, make_pair(j,k)));
                }

                if (std::chrono::duration_cast<std::chrono::minutes>(
                        std::chrono::high_resolution_clock::now() - time).count() >= config.maxTime) {
                    this->overTime = true;
                    throw std::runtime_error("Przekroczono limit czasowy");
                }
            }
        }

        std::sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) {
            return get<1>(a) <get<1>(b); // Porównanie kosztów
        });





        // Aktualizacja Tabu i najlepszej trasy
        tabu_queue.push(get<2>(candidates[0]));

        // Sprawdzenie tolerancji odchylenia od optimum
        if (get<1>(candidates[0]) - optimum <= (lb * config.SAAcceptableDeviationFromOptimum)/100.0) {
            this->best_way = get<0>(candidates[0]);
            this->cost = get<1>(candidates[0]);
            throw std::runtime_error("Wynik w granicach tolerancji odchylenia od wyniku optymalnego");
        }

        // Aktualizacja najlepszej ścieżki
        if (get<1>(candidates[0]) < this->cost) {
            this->best_way = get<0>(candidates[0]);
            this->cost = get<1>(candidates[0]);
            this->noChangesStreak = 0;
        } else {
            this->noChangesStreak++;
        }
        this->last_cost = get<1>(candidates[0]);

        if(this->noChangesStreak >= config.TabuIterationsLimit){
            throw std::runtime_error("osiągnięto limit pomiarów bez zmiany wyniku");
        }
    }
}

void TabuSearch::test_algorithm(vector<Node> nodes) {
    vector<Node*> visited;

    // Ustalenie rozmiaru listy Tabu
    if (nodes.size() < 50) {
        tabu_size = nodes.size() * 0.5;
    } else if (nodes.size() <= 500) {
        tabu_size = nodes.size() * 0.05;
    } else {
        tabu_size = nodes.size() * 0.01;
    }

    this->last_cost = cost;
    vector<double> timeMeasurements, absolutes, relatives;
    vector<int> results = vector<int>();

    for (int x = 0; x < config.repetitionsPerInstance; x++) {
        auto start = chrono::high_resolution_clock::now();
        time = start;

        try {
            // Wybór metody generowania początkowej ścieżki
            if (config.TabuUpperLimit == "nn") {

                NearestNeighbour n;
                n.time = start;
                n.nearestNeighbour(&nodes[0], nodes.size(), visited, 0, &nodes[0], 1);
                best_way = n.best_way;
                cost = n.result;
            } else {
                best_way = GenerateRandomWay(nodes);
                cost = v.calculate_value(nodes, best_way);
            }
            lb = primAlgorithm(nodes);
            // Uruchomienie głównego algorytmu
            algorithm(nodes);
        } catch (const std::runtime_error& e) {
            std::cerr << "Błąd: " << e.what() << std::endl;
        }

        auto finish = chrono::high_resolution_clock::now();
        ms_double = finish - start;
        timeMeasurements.push_back(ms_double.count() / 1000);
        results.push_back(cost);
        if (this->overTime) break;
    }

    int temp = 0;
    for (auto x : results) {
        temp += x;
    }
    temp /= results.size();

    // Obliczanie statystyk
    statCalculator s;
    vector<double> stats = s.calcStats(timeMeasurements, absolutes, relatives);
    string t = to_string(config.TabuIterationsLimit) + " " + config.Tabuchange_way_by + " " + config.TabuUpperLimit;
    s.statsOutput(stats, timeMeasurements, absolutes, relatives, best_way, temp,
                  config.showInConsole, optimum, config.outputFile, "TabuSearch", t);
}

vector<int> TabuSearch::twoOptSwap(vector<int>& route, int i, int k) {
    std::vector<int> newRoute(route);

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

int TabuSearch::calculateDiversity(const vector<int>& route1, const vector<int>& route2) {
    int diversity = 0;

    // Porównujemy krawędzie w trasach
    for (size_t i = 0; i < route1.size() - 1; ++i) {
        // Sprawdź, czy krawędź (route1[i], route1[i + 1]) istnieje w route2
        auto it = std::find(route2.begin(), route2.end(), route1[i]);
        if (it == route2.end() || *(it + 1) != route1[i + 1]) {
            diversity++; // Krawędź jest różna
        }
    }

    return diversity;
}
