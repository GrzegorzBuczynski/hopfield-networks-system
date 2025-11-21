#pragma once
#include <vector>
#include "Matrix.h" // Use full definition

using Matrix = Matrix;

class HopfieldNetwork {
private:
    Matrix weights;

public:
    HopfieldNetwork();
    void train(const std::vector<Matrix>& patterns);
    Matrix recall(Matrix input, int maxIter = 100);
};