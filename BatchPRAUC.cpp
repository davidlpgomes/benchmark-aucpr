#include "BatchPRAUC.hpp"

#include <algorithm>
#include <limits>
#include <stdlib.h>

bool compare(std::pair<double, int> a, std::pair<double, int> b) {
    return a < b;
}

double trapzArea(double x1, double x2, double y1, double y2) {
    return abs(x1 - x2) * (y1 + y2) / 2;
}

double aucPR(std::vector<int> &real, std::vector<double> &scores) {
    unsigned long p{0};

    std::vector<std::pair<double, int>> samples;
    for (unsigned long i = 0; i < real.size(); i++) {
        samples.push_back(std::make_pair(scores[i], real[i]));
        if (real[i]) p++;
    }

    unsigned long n{samples.size()};

    if (!p || p == n)
        return 0;

    std::sort(samples.begin(), samples.end(), compare);

    unsigned long fp{n - p};
    unsigned long tp{p}, tpPrev{tp};

    double auc{0}, scorePrev{std::numeric_limits<double>::max()};

    double prec{tp / (double) (tp + fp)}, precPrev{prec};

    std::vector<std::pair<double, int>>::const_iterator it{samples.begin()};
    for (; it != samples.end(); ++it) {
        if (it->first != scorePrev) {
            prec = tp / (double) (tp + fp);

            if (precPrev > prec)
                prec = precPrev; // Monotonic. decreasing

            auc += trapzArea(tp, tpPrev, prec, precPrev);

            scorePrev = it->first;
            tpPrev = tp;
            precPrev = prec;
        }

        if (it->second) tp--;
        else fp--;
    }

    auc += trapzArea(tp, tpPrev, 1.0, precPrev);

    return auc / p; // Scale the x axis
}
