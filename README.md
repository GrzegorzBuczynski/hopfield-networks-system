# 🧠 Hopfield Networks - Complete Pattern Recognition System

## 📋 Program Description

Complete pattern recognition and reconstruction system using Hopfield networks for 5x5 patterns. The program enables network training on patterns, reconstruction of distorted patterns, and pattern search in larger matrices with an English interface and improved visual formatting.

## 🚀 Compilation and Running

### Requirements
- C++17 compiler (MinGW, GCC, Clang)
- Windows system (tested on Windows 10)
- Terminal supporting ANSI color codes

### Compilation
```bash
# Using the provided batch script (recommended)
.\compile.bat

# Manual compilation
g++ -std=c++17 -O2 -Wall -Wextra -o hopfield.exe main.cpp
```

### Running
```bash
.\hopfield.exe
```

## 🎯 Main Features

### 1. **Add New Pattern** (Option 1)
- Interactive 5x5 pattern input
- Real-time preview during input
- Automatic network retraining after addition
- Input validation (0 or 1 only)

### 2. **Reconstruct Pattern** (Option 2)
- Input distorted pattern
- Automatic reconstruction by Hopfield network
- Visual difference analysis (green=match, red=fixed, yellow=lost)

### 3. **Test Pattern Recognition** (Option 3)
- Test pattern with automatic comparison
- Similarity percentage calculation to library patterns
- Detailed difference analysis

### 4. **Show Pattern Library** (Option 4)
- Browse all saved patterns
- Numbered and formatted display
- Current pattern count

### 5. **Demo Pattern Search** (Option 5)
- Search 5x5 pattern in 10x10 matrix
- Matching algorithm with noise
- Color overlay visualization with row/column numbering

### 6. **Save/Load Patterns** (Options 6-7)
- Persistent pattern storage in `patterns.txt`
- Automatic loading on startup
- Error handling for missing files

### 7. **System Information** (Option 8)
- Technical documentation
- Current session statistics
- Pause before returning to menu

### 8. **Exit** (Option 9)
- Clean program termination

## 🔧 How the Program Works

### Hopfield Network Algorithm

1. **Training (Hebb's Method):**
   ```
   W[i][j] = Σ(p[i] * p[j]) for all patterns p
   where i ≠ j (diagonal = 0)
   ```

2. **Reconstruction:**
   ```
   x[i] = sgn(Σ(W[i][j] * x[j]))
   where sgn(x) = 1 if x ≥ 0, otherwise -1
   ```

3. **Iteration to convergence:**
   - Maximum 100 iterations
   - Stop when no changes occur

### Data Structure

- **Pattern**: `std::vector<int>` (25 elements, values -1 or 1)
- **Matrix**: `std::vector<std::vector<int>>` (25x25 weight matrix)
- **5x5 Patterns**: converted to 25-element vector

## 📖 User Instructions

### First Run

1. **Run the program:**
   ```bash
   .\hopfield.exe
   ```

2. **Program automatically:**
   - Creates 4 default patterns (Square, Cross, X, Triangle T)
   - Trains network on these patterns
   - Displays main menu

### Adding Patterns

1. Select option **1**
2. Enter 0 or 1 for each 5x5 field
3. Program shows real-time preview
4. After completion, network is automatically retrained

### Testing Reconstruction

1. Select option **2** or **3**
2. Enter test pattern (may be distorted)
3. Program shows:
   - Input pattern
   - Network reconstruction
   - Color-coded difference comparison

### Pattern Search in Large Matrix

1. Select option **5**
2. Program automatically:
   - Creates 10x10 matrix with noise
   - Trains network on checkerboard pattern
   - Finds best match
   - Shows visualization with color overlay

## 🎨 Visualization

### Symbols
- `#` - filled cell (value 1) - **Cyan color**
- `.` - empty cell (value -1) - **White color**

### ANSI Colors
- **Green** `#` - matching cells (1=1)
- **Red** `#` - fixed cells (network changed 0→1)
- **Yellow** `.` - lost cells (network changed 1→0)
- **White** `.` - unchanged empty cells
- **Magenta** `#` - original pattern cells

### Formatting
- **Fixed-width display** with spaces for consistent alignment
- **Row/column numbering** for large matrices
- **Color legends** for easy interpretation

## 📁 Files

- `main.cpp` - source code
- `hopfield.exe` - compiled program
- `patterns.txt` - saved patterns file (created automatically)
- `functions_map.json` - functionality map
- `compile.bat` - compilation script
- `EXAMPLE_PATTERNS.txt` - example patterns library
- `README.md` - this documentation

## 🔍 Usage Examples

### Example 1: Basic Pattern Addition
```
1. Run program
2. Select option 1
3. Enter "T" pattern:
   0 0 1 0 0
   0 0 1 0 0
   1 1 1 1 1
   0 0 1 0 0
   0 0 1 0 0
4. Network will be retrained
```

### Example 2: Reconstruction Test
```
1. Select option 2
2. Enter distorted pattern (e.g., with errors)
3. Program shows reconstruction and differences
```

### Example 3: Pattern Search Demo
```
1. Select option 5
2. Program shows:
   - Checkerboard pattern 5x5
   - 10x10 matrix with noise
   - Best match position
   - Color overlay visualization
```

## ⚙️ Technical Parameters

- **Pattern size**: 5x5 pixels (25 neurons)
- **Maximum iterations**: 100
- **File format**: text, 25 numbers per line
- **Encoding**: UTF-8
- **C++ standard**: C++17
- **Default patterns**: 4 (Square, Cross, X, Triangle T)

## 🐛 Troubleshooting

### Problem: Colors not displaying
**Solution**: Use Windows Terminal or PowerShell instead of cmd.exe

### Problem: Compilation error
**Solution**: Check if you have C++17 compiler:
```bash
g++ --version
```

### Problem: Program doesn't find patterns
**Solution**: 
- Check if patterns are saved in `patterns.txt`
- Use option 4 to see pattern library
- Add new patterns with option 1

### Problem: Permission denied during compilation
**Solution**: Run the clean command in compile.bat or manually delete hopfield.exe

## 📚 Theory

### Hopfield Networks
Hopfield networks are recurrent neural networks used for:
- Associative memory
- Pattern recognition
- Combinatorial optimization

### Applications
- Handwriting recognition
- Image compression
- Solving NP-complete problems
- Recommendation systems

## 🆕 Recent Updates (v2.0)

- **English interface** - All text converted to English for better compatibility
- **Fixed-width formatting** - Consistent matrix display with proper spacing
- **Triangle (T) pattern** - Added to default patterns for better recognition
- **Enhanced colors** - Improved ANSI color coding and legends
- **Row/column numbering** - Better visualization for large matrices
- **Automatic cleanup** - Compilation script removes previous binary
- **Better error handling** - Improved user experience

## 👨‍💻 Author

System developed based on classical Hopfield network algorithms with visual extensions and user interface improvements.

## 📄 License

Educational program - for scientific and educational use.

---

**Note**: Program requires terminal supporting ANSI sequences for colors. On Windows, use Windows Terminal or PowerShell for best experience.