#pragma once
#include <string>
#include <vector>
#include "Matrix.h" // Use full definition

class HopfieldNetwork; // Forward declaration is sufficient here
using Matrix = Matrix;

namespace UI {

void printMenu();
void printSystemInfo(const std::string& filename, size_t pattern_count);
void printPattern(const Matrix& p);
void printPatternWithDifferences(const Matrix& original, const Matrix& recalled);
void printPatternComparison(const Matrix& original, const Matrix& recalled);
void printOverlay(const std::vector<std::vector<int>>& large, int row, int col, const Matrix& recalled);

Matrix readUserPatternWithPreview();
void showPatternLibrary(const std::vector<Matrix>& patterns);
void testPatternRecognition(const std::vector<Matrix>& patterns, HopfieldNetwork& network);
void demoPatternSearch(HopfieldNetwork& network);
bool handleMenuChoice(std::vector<Matrix>& patterns, HopfieldNetwork& network, const std::string& filename);


}; // namespace UI