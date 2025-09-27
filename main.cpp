#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <iomanip>

using Pattern = std::vector<int>;
using Matrix  = std::vector<std::vector<int>>;

void printPatternWithDifferences(const Pattern& original, const Pattern& recalled) {
    for (int i = 0; i < 25; i++) {
        if (recalled[i] == 1 && original[i] == 1) {
            std::cout << "\033[1;32m#\033[0m "; // zielone dla zgodnych
        } else if (recalled[i] == 1 && original[i] != 1) {
            std::cout << "\033[1;31m#\033[0m "; // czerwone dla roznic
        } else if (recalled[i] == -1 && original[i] == 1) {
            std::cout << "\033[1;33m.\033[0m "; // zolte dla utraconych
        } else {
            std::cout << "\033[0;37m.\033[0m "; // biale dla pustych
        }

        if ((i+1) % 5 == 0) std::cout << "\n";
    }
    std::cout << "\n";
}




Pattern flatten(const std::vector<std::vector<int>>& grid) {
    Pattern p;
    for (auto& row : grid)
        for (auto v : row)
            p.push_back(v == 1 ? 1 : -1);
    return p;
}

int sgn(int x) {
    return (x >= 0) ? 1 : -1;
}

Matrix train(const std::vector<Pattern>& patterns) {
    int n = patterns[0].size();
    Matrix W(n, std::vector<int>(n, 0));
    for (const auto& p : patterns)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j) W[i][j] += p[i] * p[j];
    return W;
}

Pattern recall(const Matrix& W, Pattern input, int maxIter = 100) {
    int n = input.size();
    for (int iter = 0; iter < maxIter; iter++) {
        bool changed = false;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) sum += W[i][j] * input[j];
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

void printPattern(const Pattern& p) {
    for (int i = 0; i < 25; i++) {
        if (p[i] == 1) {
            std::cout << "\033[1;36m#\033[0m "; // cyjan dla wypełnionych + spacja
        } else {
            std::cout << "\033[0;37m.\033[0m "; // biale dla pustych + spacja
        }
        if ((i+1) % 5 == 0) std::cout << "\n";
    }
    std::cout << "\n";
}

Pattern readUserPatternWithPreview() {
    std::vector<std::vector<int>> grid(5, std::vector<int>(5,0));
    std::cout << "Enter 5x5 pattern (0 = empty, 1 = filled):\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int val;
            while (true) {
                std::cout << "Field [" << i+1 << "," << j+1 << "]: ";
                std::cin >> val;
                if (val == 0 || val == 1) break;
                std::cout << "Enter 0 or 1!\n";
            }
            grid[i][j] = val;

            // Podglad aktualnego wzoru
            std::cout << "Current pattern:\n";
            for (int r = 0; r <= i; r++) {
                for (int c = 0; c < 5; c++) {
                    if (grid[r][c] == 1) {
                        std::cout << "\033[1;36m#\033[0m "; // cyjan dla wypełnionych
                    } else {
                        std::cout << "\033[0;37m.\033[0m "; // biale dla pustych
                    }
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
    }
    return flatten(grid);
}

void savePatterns(const std::vector<Pattern>& patterns, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) { std::cerr << "Error saving to file!\n"; return; }
    for (const auto& p : patterns) {
        for (auto v : p) out << v << " ";
        out << "\n";
    }
    out.close();
    std::cout << "Patterns saved to " << filename << "\n";
}

void loadPatterns(std::vector<Pattern>& patterns, const std::string& filename) {
    std::ifstream in(filename);
    if (!in) { 
        std::cerr << "File " << filename << " not found. Using default patterns.\n"; 
        return; 
    }
    patterns.clear();
    while (!in.eof()) {
        Pattern p;
        for (int i = 0; i < 25; i++) {
            int val;
            if (!(in >> val)) break;
            p.push_back(val);
        }
        if (p.size() == 25) patterns.push_back(p);
    }
    in.close();
    if (!patterns.empty())
        std::cout << "Patterns loaded from " << filename << "\n";
}

// --- Szukanie wzorca 5x5 w dużej macierzy 10x10 ---
int matchScore(const Matrix& large, const Matrix& small, int row, int col) {
    int score = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (large[row+i][col+j] == small[i][j])
                score++;
    return score;
}

std::pair<int,int> findBestMatch(const Matrix& large, const Matrix& small) {
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

// --- Drukowanie dużej macierzy z nakładką wzorca ---
void printOverlay(const Matrix& large, const Matrix& /*small*/, int row, int col, const Pattern& recalled) {
    for (int i = 0; i < static_cast<int>(large.size()); i++) {
        std::cout << "\033[0;37m" << std::setw(2) << i << "|\033[0m";
        for (int j = 0; j < static_cast<int>(large[0].size()); j++) {
            bool inPattern = (i >= row && i < row+5 && j >= col && j < col+5);
            if (inPattern) {
                int idx = (i-row)*5 + (j-col);
                if (recalled[idx] == 1 && large[i][j] == 1)
                    std::cout << "\033[1;32m#\033[0m "; // zielone zgodne
                else if (recalled[idx] == 1 && large[i][j] != 1)
                    std::cout << "\033[1;31m#\033[0m "; // czerwone poprawione
                else if (recalled[idx] == -1 && large[i][j] == 1)
                    std::cout << "\033[1;33m.\033[0m "; // zolte utracone
                else
                    std::cout << "\033[0;37m.\033[0m "; // biale puste
            } else {
                if (large[i][j] == 1) {
                    std::cout << "\033[1;35m#\033[0m "; // magenta dla wypełnionych
                } else {
                    std::cout << "\033[0;37m.\033[0m "; // biale dla pustych
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "\033[0;37m   +--------------------\033[0m\n";
    std::cout << "\033[0;37m    0 1 2 3 4 5 6 7 8 9\033[0m\n";
    std::cout << "\033[1;33mLegend:\033[0m \033[1;32m#\033[0m=match \033[1;31m#\033[0m=fixed \033[1;33m.\033[0m=lost \033[1;35m#\033[0m=original \033[0;37m.\033[0m=empty\n";
}

// --- Funkcje pomocnicze dla zaawansowanych funkcjonalności ---
void printPatternComparison(const Pattern& original, const Pattern& recalled) {
    std::cout << "\033[1;34m=== PATTERN COMPARISON ===\033[0m\n";
    std::cout << "\033[1;36mOriginal:\033[0m\n";
    printPattern(original);
    std::cout << "\033[1;36mReconstructed:\033[0m\n";
    printPattern(recalled);
    std::cout << "\033[1;33mDifferences:\033[0m \033[1;32m#\033[0m=match \033[1;31m#\033[0m=fixed \033[1;33m.\033[0m=lost \033[0;37m.\033[0m=empty\n";
    printPatternWithDifferences(original, recalled);
}

void demoPatternSearch() {
    std::cout << "\n\033[1;34m=== DEMO: PATTERN SEARCH IN LARGE MATRIX ===\033[0m\n";
    
    // Create large 10x10 matrix with noise
    Matrix large(10, std::vector<int>(10, 0));
    Matrix small(5, std::vector<int>(5, 0));
    
    // Pattern 5x5 (checkerboard)
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            small[i][j] = (i+j) % 2;

    // Large matrix with noise
    for (int i = 2; i < 7; i++)
        for (int j = 3; j < 8; j++)
            large[i][j] = (i+j) % 2;
    large[3][4] = 0; // noise
    large[5][5] = 0; // noise
    
    std::cout << "\033[1;36mPattern to search (5x5):\033[0m\n";
    printPattern(flatten(small));
    
    std::cout << "\033[1;35mLarge matrix (10x10) with noise:\033[0m\n";
    for (int i = 0; i < 10; i++) {
        std::cout << "\033[0;37m" << std::setw(2) << i << "|\033[0m";
        for (int j = 0; j < 10; j++) {
            if (large[i][j] == 1) {
                std::cout << "\033[1;35m#\033[0m "; // magenta dla wypełnionych
            } else {
                std::cout << "\033[0;37m.\033[0m "; // biale dla pustych
            }
        }
        std::cout << "\n";
    }
    std::cout << "\033[0;37m   +--------------------\033[0m\n";
    std::cout << "\033[0;37m    0 1 2 3 4 5 6 7 8 9\033[0m\n";
    
    // Train network on pattern
    std::vector<Pattern> patterns = { flatten(small) };
    Matrix W = train(patterns);

    // Find best match
    auto result = findBestMatch(large, small);
    int r = result.first, c = result.second;
    std::cout << "\nBest match at position: (" << r << "," << c << ")\n";
    
    // Extract fragment and reconstruct
    Matrix fragment(5, std::vector<int>(5));
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            fragment[i][j] = large[r+i][c+j];

    Pattern inputPattern = flatten(fragment);
    Pattern recalled = recall(W, inputPattern);

    std::cout << "Fragment from large matrix:\n";
    printPattern(inputPattern);
    std::cout << "Reconstruction by Hopfield network:\n";
    printPattern(recalled);
    
    std::cout << "\033[1;33mVisualization with overlay:\033[0m\n";
    printOverlay(large, small, r, c, recalled);
}

void showPatternLibrary(const std::vector<Pattern>& patterns) {
    std::cout << "\n=== PATTERN LIBRARY ===\n";
    if (patterns.empty()) {
        std::cout << "No patterns in library.\n";
        return;
    }
    
    for (size_t i = 0; i < patterns.size(); i++) {
        std::cout << "Pattern " << (i+1) << ":\n";
        printPattern(patterns[i]);
        std::cout << "\n";
    }
}

void testPatternRecognition(const std::vector<Pattern>& patterns, const Matrix& W) {
    if (patterns.empty()) {
        std::cout << "No patterns to test.\n";
        return;
    }
    
    std::cout << "\n=== PATTERN RECOGNITION TEST ===\n";
    std::cout << "Enter test pattern (may be distorted):\n";
    Pattern testPattern = readUserPatternWithPreview();
    
    std::cout << "Test pattern:\n";
    printPattern(testPattern);
    
    Pattern recalled = recall(W, testPattern);
    std::cout << "Reconstruction result:\n";
    printPattern(recalled);
    
    // Check similarity to library patterns
    std::cout << "\nComparison with library patterns:\n";
    for (size_t i = 0; i < patterns.size(); i++) {
        int matches = 0;
        for (int j = 0; j < 25; j++) {
            if (recalled[j] == patterns[i][j]) matches++;
        }
        std::cout << "Similarity to pattern " << (i+1) << ": " 
                  << (matches * 100 / 25) << "%\n";
        printPatternComparison(patterns[i], recalled);
    }
}

int main() {
    std::vector<Pattern> patterns;
    std::string defaultFile = "patterns.txt";
    Matrix W;

    std::cout << "=== HOPFIELD NETWORKS - COMPLETE SYSTEM ===\n";
    std::cout << "Pattern recognition and reconstruction system 5x5\n\n";

    // Try to load patterns from file
    loadPatterns(patterns, defaultFile);

    // If no file or loaded patterns -> default patterns
    if (patterns.empty()) {
        std::cout << "Creating default patterns...\n";
        std::vector<std::vector<std::vector<int>>> grids = {
            { {1,1,1,1,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,1,1,1,1} }, // Square
            { {0,0,1,0,0}, {0,0,1,0,0}, {1,1,1,1,1}, {0,0,1,0,0}, {0,0,1,0,0} }, // Cross
            { {1,0,0,0,1}, {0,1,0,1,0}, {0,0,1,0,0}, {0,1,0,1,0}, {1,0,0,0,1} }, // X
            { {0,0,1,0,0}, {0,1,0,1,0}, {1,1,1,1,1}, {0,0,0,0,0}, {0,0,0,0,0} }  // Triangle (T)
        };
        for (auto& g : grids) patterns.push_back(flatten(g));
        std::cout << "Created " << patterns.size() << " default patterns.\n";
    }

    W = train(patterns);
    std::cout << "Network trained on " << patterns.size() << " patterns.\n";

    while (true) {
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
        
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Pattern newP = readUserPatternWithPreview();
                patterns.push_back(newP);
                W = train(patterns);
                std::cout << "Added new pattern and retrained network!\n";
                std::cout << "Total patterns: " << patterns.size() << "\n";
                break;
            }
            case 2: {
                Pattern input = readUserPatternWithPreview();
                std::cout << "Input:\n";
                printPattern(input);
                Pattern recalled = recall(W, input);
                std::cout << "Reconstructed pattern:\n";
                printPattern(recalled);
                printPatternComparison(input, recalled);
                break;
            }
            case 3: {
                testPatternRecognition(patterns, W);
                break;
            }
            case 4: {
                showPatternLibrary(patterns);
                break;
            }
            case 5: {
                demoPatternSearch();
                break;
            }
            case 6: {
                savePatterns(patterns, defaultFile);
                break;
            }
            case 7: {
                loadPatterns(patterns, defaultFile);
                if (!patterns.empty()) {
                    W = train(patterns);
                    std::cout << "Network retrained on " << patterns.size() << " patterns.\n";
                }
                break;
            }
            case 8: {
                std::cout << "\n=== SYSTEM INFORMATION ===\n";
                std::cout << "Hopfield Networks - pattern recognition system\n";
                std::cout << "- Patterns: 5x5 pixels (values -1 or 1)\n";
                std::cout << "- Training: Hebb's method (sum of products)\n";
                std::cout << "- Reconstruction: iterative update until convergence\n";
                std::cout << "- Functions: add patterns, reconstruction, search\n";
                std::cout << "- Save/load: file " << defaultFile << "\n";
                std::cout << "- ANSI colors: green=match, red=fixed\n";
                std::cout << "Current patterns: " << patterns.size() << "\n";
                break;
            }
            case 9: {
                std::cout << "Thank you for using the system!\n";
                return 0;
            }
            default: {
                std::cout << "Invalid choice. Select option 1-9.\n";
                break;
            }
        }
    }
    return 0;
}


