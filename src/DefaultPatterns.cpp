#include "DefaultPatterns.h"
#include "Matrix.h"
#include <vector>

std::vector<Matrix> createDefaultPatterns() {
    std::vector<Matrix> patterns;
    // Wzorzec 1: Kwadrat
    patterns.push_back(Matrix::fromGrid({
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    }));

    // Wzorzec 2: Krzyż
    patterns.push_back(Matrix::fromGrid({
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}
    }));

    // Wzorzec 3: X
    patterns.push_back(Matrix::fromGrid({
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1}
    }));

    return patterns;
}