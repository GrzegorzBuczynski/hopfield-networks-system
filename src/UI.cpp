#include "UI.h"
#include "HopfieldNetwork.h"
#include "Pattern.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits> // <-- 1. Dodajemy brakujący nagłówek
#include <cmath>
#include "FileUtils.h" // Potrzebne dla save/load

namespace UI {

void printMenu() {
    std::cout << "\n=== MAIN MENU ===\n";
    std::cout << "1 - Add new 5x5 pattern\n";
    std::cout << "2 - Reconstruct pattern from input\n";
    std::cout << "3 - Test pattern recognition\n";
    std::cout << "4 - Show pattern library\n";
    std::cout << "5 - Demo pattern search in large matrix\n";
    std::cout << "6 - Save patterns to file\n";
    std::cout << "7 - Load patterns from file\n";
    std::cout << "8 - System information\n";
    std::cout << "9 - Exit\n";
    std::cout << "Choice: ";
}

void printSystemInfo(const std::string& filename, size_t pattern_count) {
    std::cout << "\n=== SYSTEM INFORMATION ===\n";
    std::cout << "Hopfield Networks - pattern recognition system\n";
    std::cout << "- Patterns: 5x5 pixels (values -1 or 1)\n";
    std::cout << "- Training: Hebb's method (sum of products)\n";
    std::cout << "- Reconstruction: iterative update until convergence\n";
    std::cout << "- Functions: add patterns, reconstruction, search\n";
    std::cout << "- Save/load: file " << filename << "\n";
    std::cout << "- ANSI colors: green=match, red=fixed\n";
    std::cout << "Current patterns: " << pattern_count << "\n";
}

void printPattern(const Matrix& p) {
    const int width = static_cast<int>(sqrt(p.size()));
    for (size_t i = 0; i < p.size(); i++) {
        if (p[i] == 1) {
            std::cout << "\033[1;36m#\033[0m "; // cyjan
        } else {
            std::cout << "\033[0;37m#\033[0m "; // biale
        }
        if ((i + 1) % width == 0) std::cout << "\n";
    }
    std::cout << "\n";
}

void printPatternWithDifferences(const Matrix& original, const Matrix& recalled) {
    const int width = static_cast<int>(sqrt(original.size()));
    for (size_t i = 0; i < original.size(); i++) {
        if (recalled[i] == 1 && original[i] == 1) {
            std::cout << "\033[1;32m#\033[0m "; // zielone
        } else if (recalled[i] == 1 && original[i] != 1) {
            std::cout << "\033[1;31m#\033[0m "; // czerwone
        } else if (recalled[i] == -1 && original[i] == 1) {
            std::cout << "\033[1;33m.\033[0m "; // zolte
        } else {
            std::cout << "\033[0;37m#\033[0m "; // biale
        }
        if ((i + 1) % width == 0) std::cout << "\n";
    }
    std::cout << "\n";
}

void printPatternComparison(const Matrix& original, const Matrix& recalled) {
    std::cout << "\033[1;34m=== PATTERN COMPARISON ===\033[0m\n";
    std::cout << "\033[1;36mOriginal:\033[0m\n";
    printPattern(original);
    std::cout << "\033[1;36mReconstructed:\033[0m\n";
    printPattern(recalled);
    std::cout << "\033[1;33mDifferences:\033[0m \033[1;32m#\033[0m=match \033[1;31m#\033[0m=fixed \033[1;33m.\033[0m=lost \033[0;37m#\033[0m=empty\n";
    printPatternWithDifferences(original, recalled);
}

Matrix readUserPatternWithPreview() {
    // Na razie zostawiamy sztywny rozmiar 5x5 dla wprowadzania ręcznego
    const int height = 5;
    const int width = 5;
    std::vector<std::vector<int>> grid(height, std::vector<int>(width, 0));
    std::cout << "Enter 5x5 pattern (0 = empty, 1 = filled):\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int val;
            while (true) {
                std::cout << "Field [" << i + 1 << "," << j + 1 << "]: ";
                std::cin >> val;
                if (!std::cin.fail() && (val == 0 || val == 1)) break;
                std::cout << "Enter 0 or 1!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            grid[i][j] = val;

            std::cout << "Current pattern:\n";
            for (int r = 0; r < height; r++) {
                for (int c = 0; c < width; c++) {
                    if (r > i || (r == i && c > j)) {
                         std::cout << "  ";
                         continue;
                    }
                    if (grid[r][c] == 1) {
                        std::cout << "\033[1;36m#\033[0m ";
                    } else {
                        std::cout << "\033[0;37m#\033[0m ";
                    }
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
    }
    return Matrix::fromGrid(grid);
}

void showPatternLibrary(const std::vector<Matrix>& patterns) {
    std::cout << "\n=== PATTERN LIBRARY ===\n";
    if (patterns.empty()) {
        std::cout << "No patterns in library.\n";
        return;
    }
    for (size_t i = 0; i < patterns.size(); i++) {
        std::cout << "Pattern " << (i + 1) << ":\n";
        printPattern(patterns[i]);
        std::cout << "\n";
    }
}

void testPatternRecognition(const std::vector<Matrix>& patterns, HopfieldNetwork& network) {
    if (patterns.empty()) {
        std::cout << "No patterns to test.\n";
        return;
    }
    std::cout << "\n=== PATTERN RECOGNITION TEST ===\n";
    std::cout << "Enter test pattern (may be distorted):\n";
    Matrix testPattern = readUserPatternWithPreview();
    
    std::cout << "Test pattern:\n";
    printPattern(testPattern);
    
    Matrix recalled = network.recall(testPattern);
    std::cout << "Reconstruction result:\n";
    printPattern(recalled);
    
    std::cout << "\nComparison with library patterns:\n";
    for (size_t i = 0; i < patterns.size(); i++) {
        int matches = 0;
        for (size_t j = 0; j < recalled.size(); j++) {
            if (recalled[j] == patterns[i][j]) matches++;
        }
        std::cout << "Similarity to pattern " << (i + 1) << ": " 
                  << (matches * 100 / recalled.size()) << "%\n";
        printPatternComparison(patterns[i], recalled);
    }
}

namespace { // Prywatne funkcje pomocnicze dla tego pliku (pozostaje puste lub można przenieść resztę)
    int matchScore(const std::vector<std::vector<int>>& large, const std::vector<std::vector<int>>& small, int row, int col) {
        int score = 0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (large[row + i][col + j] == small[i][j])
                    score++;
        return score;
    }

    std::pair<int,int> findBestMatch(const std::vector<std::vector<int>>& large, const std::vector<std::vector<int>>& small) {
        int bestScore = -1, bestRow = -1, bestCol = -1;
        for (int i = 0; i <= static_cast<int>(large.size()) - 5; i++)
            for (int j = 0; j <= static_cast<int>(large[0].size()) - 5; j++) {
                int score = matchScore(large, small, i, j);
                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i; bestCol = j;
                }
            }
        return {bestRow, bestCol};
    }
}

void printOverlay(const std::vector<std::vector<int>>& large, int row, int col, const Matrix& recalled) {
    for (int i = 0; i < static_cast<int>(large.size()); i++) {
        std::cout << "\033[0;37m" << std::setw(2) << i << "|\033[0m";
        for (int j = 0; j < static_cast<int>(large[0].size()); j++) {
            bool inPattern = (i >= row && i < row+5 && j >= col && j < col+5);
            if (inPattern) {
                int idx = (i-row)*5 + (j-col);
                if (recalled[idx] == 1 && large[i][j] == 1) std::cout << "\033[1;32m#\033[0m ";
                else if (recalled[idx] == 1 && large[i][j] != 1) std::cout << "\033[1;31m#\033[0m ";
                else if (recalled[idx] == -1 && large[i][j] == 1) std::cout << "\033[1;33m.\033[0m ";
                else std::cout << "\033[0;37m#\033[0m ";
            } else {
                if (large[i][j] == 1) std::cout << "\033[1;35m#\033[0m ";
                else std::cout << "\033[0;37m#\033[0m ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\033[0;37m   +--------------------\033[0m\n";
    std::cout << "\033[0;37m    0 1 2 3 4 5 6 7 8 9\033[0m\n";
    std::cout << "\033[1;33mLegend:\033[0m \033[1;32m#\033[0m=match \033[1;31m#\033[0m=fixed \033[1;33m.\033[0m=lost \033[1;35m#\033[0m=original \033[0;37m#\033[0m=empty\n";
}

void demoPatternSearch(HopfieldNetwork& network) {
    std::cout << "\n\033[1;34m=== DEMO: PATTERN SEARCH IN LARGE MATRIX ===\033[0m\n";
    
    std::vector<std::vector<int>> small(5, std::vector<int>(5, 0));
    for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) small[i][j] = (i+j) % 2;

    std::vector<std::vector<int>> large(10, std::vector<int>(10, 0));
    for (int i = 2; i < 7; i++) for (int j = 3; j < 8; j++) large[i][j] = (i+j) % 2;
    large[3][4] = 0; large[5][5] = 0;
    
    network.train({Matrix::fromGrid(small)});

    auto result = findBestMatch(large, small);
    int r = result.first, c = result.second;
    
    std::vector<std::vector<int>> fragment(5, std::vector<int>(5));
    for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) fragment[i][j] = large[r+i][c+j];

    Matrix recalled = network.recall(Matrix::fromGrid(fragment));

    std::cout << "\033[1;33mVisualization with overlay:\033[0m\n";
    printOverlay(large, r, c, recalled);
}

bool handleMenuChoice(std::vector<Matrix>& patterns, HopfieldNetwork& network, const std::string& filename) {
    int choice;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        choice = 0; // Ustawienie na 0, aby wywołać domyślną opcję w switch
    }

    switch (choice) {
        case 1: {
            Matrix newP = UI::readUserPatternWithPreview();
            patterns.push_back(newP);
            network.train(patterns);
            std::cout << "Added new pattern and retrained network!\n";
            std::cout << "Total patterns: " << patterns.size() << "\n";
            break;
        }
        case 2: {
            Matrix input = UI::readUserPatternWithPreview();
            std::cout << "Input:\n";
            UI::printPattern(input);
            Matrix recalled = network.recall(input);
            std::cout << "Reconstructed pattern:\n";
            UI::printPattern(recalled);
            UI::printPatternComparison(input, recalled);
            break;
        }
        case 3: {
            UI::testPatternRecognition(patterns, network);
            break;
        }
        case 4: {
            UI::showPatternLibrary(patterns);
            break;
        }
        case 5: {
            UI::demoPatternSearch(network);
            break;
        }
        case 6: {
            savePatterns(patterns, filename);
            break;
        }
        case 7: {
            loadPatterns(patterns, filename);
            if (!patterns.empty()) {
                network.train(patterns);
                std::cout << "Network retrained on " << patterns.size() << " patterns.\n";
            }
            break;
        }
        case 8: {
            UI::printSystemInfo(filename, patterns.size());
            break;
        }
        case 9: {
            std::cout << "Thank you for using the system!\n";
            return false; // Sygnał do zakończenia pętli
        }
        default: {
            std::cout << "Invalid choice. Select option 1-9.\n";
            break;
        }
    }
    return true; // Kontynuuj pętlę
}

} // namespace UI