#pragma once

#include <vector>
#include <string>
#include "Matrix.h" // Use full definition

using Matrix = Matrix;

void savePatterns(const std::vector<Matrix>& patterns, const std::string& filename);
void loadPatterns(std::vector<Matrix>& patterns, const std::string& filename);