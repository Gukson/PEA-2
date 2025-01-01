//
// Created by Kuba on 31/12/2024.
//

#include "statCalculator.h"

void statCalculator::statsOutput(vector<double> stats, vector<double> timeMeasurements, vector<double> absolutes,
                                 vector<double> relatives, vector<int> best_way, int wynik, bool show, int bestWynik,
                                 string filename, string algos) {
    ofstream outputFile;
    outputFile.open("../data/output/" + filename, std::ios_base::app);
    outputFile << algos << " - " << best_way.size()-1 << endl;
    outputFile << "Średni czas;" << stats[0] << endl;
    outputFile << "Średni błąd bezwzględny;" << stats[1] << "s" << endl;
    outputFile << "Średni błąd bezwzględny;" << stats[1] * 100 << "%" << endl;
    outputFile << "Średni błąd względny;" << stats[2] * 100 << "%" << endl;
    outputFile << endl;
    outputFile << "Uzyskano wynik: " << wynik << endl;

    outputFile << "Błąd względny wyniku: " << abs(wynik-bestWynik)/bestWynik << endl;

    outputFile << "Błąd bezwzględny wyniku: " << abs(wynik-bestWynik) << endl;

    outputFile << "Ścieżka z powyższym wynikiem: ";
    for (int x: best_way) {
        outputFile << x << " ";
    }
    outputFile << endl;
    outputFile << endl;
    outputFile << "LP;czas;blad bezwzgledny;blad wzgledny" << endl;
    for (int x = 0; x < timeMeasurements.size(); x++) {
        outputFile << x + 1 << ";" << timeMeasurements[x] << ";" << absolutes[x] << ";" << relatives[x]
                   << endl;
    }
    outputFile << endl;

    if(show){
        cout << algos << " - " << best_way.size()-1 << endl;
        cout << "Średni czas;" << stats[0] << endl;
        cout << "Średni błąd bezwzględny;" << stats[1] << "s" << endl;
        cout << "Średni błąd bezwzględny;" << stats[1] * 100 << "%" << endl;
        cout << "Średni błąd względny;" << stats[2] * 100 << "%" << endl;
        cout << endl;
        cout << "Uzyskano wynik: " << wynik << endl;
        cout << "Błąd względny wyniku: " << abs(wynik-bestWynik)/bestWynik << endl;
        cout << "Błąd bezwzględny wyniku: " << abs(wynik-bestWynik) << endl;
        cout << "Ścieżka z powyższym wynikiem: ";
        for (int x: best_way) {
            cout << x << " ";
        }
        cout << endl;
//        cout << "LP czas blad bezwzgledny blad wzgledny" << endl;
//        for (int x = 0; x < timeMeasurements.size(); x++) {
//            cout << x + 1 << ";" << timeMeasurements[x] << ";" << absolutes[x] << ";" << relatives[x]
//                 << endl;
//        }
//        cout << endl;
    }

}

vector<double> statCalculator::calcStats(vector<double> time, vector<double> &absolute, vector<double> &relative) {
    double avgTime;
    double sum = 0.0;
    for (double t: time) {
        sum += t;
    }
    avgTime = sum / time.size();

    //liczenie błędu bezwzględnego

    //wektor absolut posiada błędy bezwzględne każdego z pomiarów
    for (double t: time) {
        absolute.push_back(abs(t - avgTime));
    }

    double avgAbsolute = 0.0;
    for (double t: absolute) {
        avgAbsolute += t;
    }
    avgAbsolute = avgAbsolute / absolute.size();

    //liczenie średniego błędu względnego

    //wektor relative posiada błędy względne każdego z pomiarów
    for (double t: time) {
        relative.push_back(abs(t - avgTime) / avgTime);
    }

    double avgRelative = 0.0;
    for (double t: relative) {
        avgRelative += t;
    }
    avgRelative = avgRelative / absolute.size();

    vector<double> results = vector<double>();
    results.push_back(avgTime);
    results.push_back(avgAbsolute);
    results.push_back(avgRelative);

    return results;
}
