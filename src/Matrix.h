#pragma once

#include <vector>
#include <string>

class Matrix {
private:
    std::vector<int> data;
    int rows;
    int cols;

public:
    Matrix();
    Matrix(int r, int c, int initial_val = 0);

    // Metoda fabryczna do tworzenia z siatki 2D (zastępuje flatten)
    static Matrix fromGrid(const std::vector<std::vector<int>>& grid); // Deklaracja pozostaje

    int& at(int r, int c);
    const int& at(int r, int c) const;

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    int num_rows() const;
    int num_cols() const;
    size_t size() const;
};