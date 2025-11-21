#include "FileUtils.h"
#include "Pattern.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "DefaultPatterns.h"

void savePatterns(const std::vector<Matrix>& patterns, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < patterns.size(); ++i) {
        const auto& p = patterns[i];
        int rows = p.num_rows();
        int cols = p.num_cols();

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                // Zapisujemy 0 zamiast -1 dla czytelności
                file << (p.at(r, c) == 1 ? 1 : 0);
                if (c < cols - 1) {
                    file << " ";
                }
            }
            file << "\n";
        }

        // Dodaj pustą linię po każdym wzorze, z wyjątkiem ostatniego
        if (i < patterns.size() - 1) {
            file << "\n";
        }
    }
    std::cout << "Patterns saved to " << filename << std::endl;
}

void loadPatterns(std::vector<Matrix>& patterns, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Info: Could not open file for reading: " << filename << ". Starting with default patterns." << std::endl;        
        if (patterns.empty()) {
            patterns = createDefaultPatterns();
    }
        return;
    }

    patterns.clear();
    std::string line;
    std::vector<std::vector<int>> currentGrid;

    while (std::getline(file, line)) {
        if (line.empty()) { // Pusta linia oddziela wzory
            if (!currentGrid.empty()) {
                patterns.push_back(Matrix::fromGrid(currentGrid));
                currentGrid.clear();
            }
        } else {
            std::vector<int> row;
            std::stringstream ss(line);
            int val;
            while (ss >> val) {
                // Konwertujemy 0/1 z pliku na -1/1 dla sieci
                row.push_back(val == 1 ? 1 : -1);
            }
            currentGrid.push_back(row);
        }
    }
    if (!currentGrid.empty()) { // Dodaj ostatni wzór, jeśli plik nie kończy się pustą linią
        patterns.push_back(Matrix::fromGrid(currentGrid));
    }
    std::cout << "Patterns loaded from " << filename << std::endl;

}