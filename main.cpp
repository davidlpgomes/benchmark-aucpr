#include <cstring>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

#include "BatchPRAUC.hpp"
#include "RollingPRAUC.hpp"


int main(int argc, char **argv) {
    if (argc < 5) {
        std::cout << "Usage: " << argv[0] << \
            " -f <path to the CSV file> " << \
            "-w <window size>" << std::endl;

        return 1;
    }

    unsigned long w{(unsigned) atol(argv[4])};

    std::ifstream file;
    file.open(argv[2]);

    double score, batch_auc, roll_auc;
    int y;

    std::vector<double> window_scores;
    std::vector<int> window_real;

    rollingprauc::RollingPRAUC r_aucpr(1, w);

    clock_t start, stop;
    double time_batch{0.0}, time_roll{0.0};

    std::string line;
    std::getline(file, line); // Discard columns name line

    while (std::getline(file, line)) {
        score = std::stod(line.substr(2));
        y = std::stoi(line.substr(0, 1));

        if (window_scores.size() == w) {
            window_scores.erase(window_scores.begin());
            window_real.erase(window_real.begin());
        }

        window_scores.push_back(score);
        window_real.push_back(y);

        start = clock();
        r_aucpr.update(y, score);
        roll_auc = r_aucpr.get();
        stop = clock();
        time_roll += (double) (stop - start) / (double) CLOCKS_PER_SEC;

        start = clock();
        batch_auc = aucPR(window_real, window_scores);
        stop = clock();
        time_batch += (double) (stop - start) / (double) CLOCKS_PER_SEC;

        if (abs(batch_auc - roll_auc) > 1e-9) {
            std::cout << "AUCs dont't match! Aborting..." << std::endl;
            return 1;
        }
    }

    double ratio = time_batch / time_roll;

    std::cout << "Batch: " << time_batch << std::endl << \
        "Rolling: " << time_roll << std::endl << \
        "Ratio: " << ratio << std::endl;

    file.close();

    return 0;
}
