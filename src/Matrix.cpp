#include "Matrix.h"

Matrix::Matrix() : data(), rows(0), cols(0) {}

Matrix::Matrix(int r, int c, int initial_val) 
    : data(r * c, initial_val), rows(r), cols(c) {}

Matrix Matrix::fromGrid(const std::vector<std::vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return Matrix();
    }
    int rows = grid.size();
    int cols = grid[0].size();
    Matrix p(rows, cols);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            p.at(r, c) = (grid[r][c] == 1 ? 1 : -1);
        }
    }
    return p;
}

int& Matrix::at(int r, int c) {
    return data[r * cols + c];
}

const int& Matrix::at(int r, int c) const {
    return data[r * cols + c];
}

int& Matrix::operator[](size_t index) {
    return data[index];
}

const int& Matrix::operator[](size_t index) const {
    return data[index];
}

int Matrix::num_rows() const {
    return rows;
}

int Matrix::num_cols() const {
    return cols;
}

size_t Matrix::size() const {
    return data.size();
}