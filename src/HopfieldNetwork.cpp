#include "HopfieldNetwork.h"
#include "Pattern.h"

namespace {
    int sgn(int x) {
        return (x >= 0) ? 1 : -1;
    }
}

HopfieldNetwork::HopfieldNetwork() : weights() {}

void HopfieldNetwork::train(const std::vector<Matrix>& patterns) {
    if (patterns.empty()) {
        weights = Matrix();
        return;
    }

    int n = static_cast<int>(patterns[0].size());
    weights = Matrix(n, n);
    for (const auto& p : patterns) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) weights.at(i, j) += p[i] * p[j];
            }
        }
    }
}

Matrix HopfieldNetwork::recall(Matrix input, int maxIter) {
    int n = static_cast<int>(input.size());
    for (int iter = 0; iter < maxIter; iter++) {
        bool changed = false;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) sum += weights.at(i, j) * input[j];
            int newState = sgn(sum);
            if (newState != input[i]) {
                input[i] = newState;
                changed = true;
            }
        }
        if (!changed) break;
    }
    return input;
}