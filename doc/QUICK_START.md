# 🚀 Quick Start - Hopfield Networks System

## ⚡ Compilation and Running (30 seconds)

### 1. Compilation
```bash
# Using the provided batch script (recommended)
.\compile.bat

# Manual compilation
g++ -std=c++17 -O2 -Wall -Wextra -o hopfield.exe main.cpp
```

### 2. Running
```bash
.\hopfield.exe
```

## 🎯 First Steps (5 minutes)

### Step 1: Check default patterns
- Program automatically creates 4 patterns (Square, Cross, X, Triangle T)
- Select option **4** to see the pattern library

### Step 2: Add your pattern
- Select option **1**
- Enter 0 (empty) or 1 (filled) for each 5x5 field
- Program shows real-time preview

### Step 3: Test reconstruction
- Select option **2**
- Enter a distorted pattern
- See how the network reconstructs it

### Step 4: Pattern search demo
- Select option **5**
- See how the program finds patterns in a large matrix

## 📋 Menu Overview

| Option | What it does | When to use |
|--------|--------------|-------------|
| **1** | Add pattern | Want to teach the network a new pattern |
| **2** | Reconstruct pattern | Have a distorted pattern to fix |
| **3** | Test recognition | Want to check similarity to library patterns |
| **4** | Show pattern library | Want to see all saved patterns |
| **5** | Demo pattern search | Want to see pattern search in matrix |
| **6** | Save patterns | Want to save patterns for later |
| **7** | Load patterns | Want to load saved patterns |
| **8** | System information | Want to learn more about the system |
| **9** | Exit | End of work |

## 🎨 Symbols and Colors

- `#` = filled cell (value 1) - **Cyan color**
- `.` = empty cell (value -1) - **White color**
- **Green** `#` = matching cells
- **Red** `#` = fixed by network
- **Yellow** `.` = lost cells
- **Magenta** `#` = original pattern cells

## 🔧 Troubleshooting

### Problem: Colors not showing
**Solution**: Use Windows Terminal or PowerShell instead of cmd.exe

### Problem: Compilation error
**Solution**: Check if you have C++17 compiler:
```bash
g++ --version
```

### Problem: Permission denied
**Solution**: The compile.bat script automatically handles this

## 📁 Project Files

- `main.cpp` - source code
- `hopfield.exe` - program (after compilation)
- `patterns.txt` - patterns (created automatically)
- `compile.bat` - compilation script
- `functions_map.json` - functionality map
- `README.md` - full documentation
- `COMPILE_INSTRUCTIONS.md` - compilation instructions
- `EXAMPLE_PATTERNS.txt` - example patterns
- `QUICK_START.md` - this file

## 🎯 Example Patterns

### Square
```
#####
#   #
#   #
#   #
#####
```

### Cross
```
  #  
  #  
#####
  #  
  #  
```

### X
```
#   #
 # # 
  #  
 # # 
#   #
```

### Triangle (T) - NEW!
```
  #  
 # # 
#####
     
     
```

## ⚡ Quick Tests

### Test 1: Check functionality
```bash
echo "4" | .\hopfield.exe
```

### Test 2: Pattern search demo
```bash
echo "5" | .\hopfield.exe
```

### Test 3: System information
```bash
echo "8" | .\hopfield.exe
```

## 🆕 What's New in v2.0

- **English interface** - All text in English
- **Fixed-width formatting** - Better matrix display
- **Triangle (T) pattern** - Added to default patterns
- **Enhanced colors** - More visual distinction
- **Row/column numbering** - Better large matrix visualization
- **Automatic cleanup** - Compilation script removes old binary

## 🎓 What's Next?

1. **Experiment** with different patterns
2. **Test** reconstruction of distorted patterns
3. **Add** your own patterns to the library
4. **Save** patterns to file
5. **Read** full documentation in README.md

## 💡 Tips

- 5x5 patterns are optimal for this system
- Network works better with distinct shapes
- More patterns = better recognition
- Distorted patterns are automatically fixed
- Use Windows Terminal for best color display

## 🚀 Advanced Features

### Pattern Comparison
- Visual difference analysis
- Color-coded matching
- Similarity percentage

### Large Matrix Search
- 10x10 matrix with noise
- Best match algorithm
- Color overlay visualization

### Real-time Preview
- Live pattern preview during input
- Input validation
- Immediate feedback

---

**Ready to start?** Run `.\hopfield.exe` and select option 4!