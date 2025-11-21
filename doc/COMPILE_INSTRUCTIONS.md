# 🔧 Compilation Instructions - Hopfield Networks System

## System Requirements

### Windows
- **Compiler**: MinGW-w64, MSYS2, or Visual Studio 2019+
- **C++ Standard**: C++17 or newer
- **Terminal**: Windows Terminal, PowerShell, or cmd.exe (Windows Terminal recommended for colors)

### Linux/macOS
- **Compiler**: GCC 7+, Clang 5+
- **C++ Standard**: C++17 or newer

## Quick Compilation

### Using the provided script (Recommended)
```bash
# Windows
.\compile.bat

# The script will:
# - Check for source file
# - Remove previous binary
# - Compile with optimal flags
# - Show file information
# - Optionally run the program
```

### Manual compilation
```bash
# Windows
g++ -std=c++17 -O2 -Wall -Wextra -o hopfield.exe main.cpp

# Linux/macOS
g++ -std=c++17 -O2 -Wall -Wextra -o hopfield main.cpp
```

## Detailed Compilation Options

### Windows (MinGW)
```bash
# Basic compilation
g++ -std=c++17 -O2 -Wall -Wextra -o hopfield.exe main.cpp

# Debug compilation
g++ -std=c++17 -g -Wall -Wextra -o hopfield_debug.exe main.cpp

# Maximum optimization
g++ -std=c++17 -O3 -march=native -Wall -Wextra -o hopfield_fast.exe main.cpp

# Small size optimization
g++ -std=c++17 -Os -s -o hopfield_small.exe main.cpp
```

### Linux/macOS
```bash
# Basic compilation
g++ -std=c++17 -O2 -Wall -Wextra -o hopfield main.cpp

# Debug compilation
g++ -std=c++17 -g -Wall -Wextra -o hopfield_debug main.cpp

# Maximum optimization
g++ -std=c++17 -O3 -march=native -Wall -Wextra -o hopfield_fast main.cpp

# Small size optimization
g++ -std=c++17 -Os -s -o hopfield_small main.cpp
```

## Running the Program

### Windows
```cmd
# In cmd.exe
hopfield.exe

# In PowerShell
.\hopfield.exe

# In Windows Terminal
./hopfield.exe
```

### Linux/macOS
```bash
./hopfield
```

## Compilation Testing

### Check compiler version
```bash
g++ --version
```

### Test compilation
```bash
# Basic test
g++ -std=c++17 -o test_compile main.cpp

# Check if executable was created
ls -la hopfield*

# Test run
echo "9" | ./hopfield
```

## Troubleshooting

### Error: "g++ not found"
**Windows:**
- Install MinGW-w64 or MSYS2
- Add to PATH: `C:\msys64\mingw64\bin`
- Or use the provided compile.bat script

**Linux:**
```bash
sudo apt install g++  # Ubuntu/Debian
sudo yum install gcc-c++  # CentOS/RHEL
```

### Error: "C++17 not supported"
**Solution:**
- Update compiler to version supporting C++17
- Use `-std=c++14` as fallback (may require code modifications)

### Error: "Permission denied" during compilation
**Solution:**
- Close any running instances of hopfield.exe
- Use the compile.bat script (handles this automatically)
- Or manually delete the executable before recompiling

### Warning: "structured binding not supported"
**Solution:**
- Use C++17 or newer compiler
- Code has been adapted for older versions

### Compilation warnings
```bash
# Compilation without warnings
g++ -std=c++17 -O2 -Wall -Wextra -Werror -o hopfield.exe main.cpp

# Compilation ignoring warnings
g++ -std=c++17 -O2 -o hopfield.exe main.cpp
```

## Optimization Options

### For performance
```bash
g++ -std=c++17 -O3 -march=native -DNDEBUG -o hopfield.exe main.cpp
```

### For debugging
```bash
g++ -std=c++17 -g -O0 -DDEBUG -o hopfield_debug.exe main.cpp
```

### For small size
```bash
g++ -std=c++17 -Os -s -o hopfield_small.exe main.cpp
```

## Example Scripts

### Windows (compile.bat) - Current Version
```batch
@echo off
setlocal enabledelayedexpansion

REM ========================================
REM Hopfield Networks - Compilation Script
REM Version 2.0 - English Interface
REM ========================================

set "EXECUTABLE=hopfield"
set "CXX=g++"
set "CXXFLAGS=-std=c++17 -O2 -Wall -Wextra"

echo.
echo ========================================
echo   HOPFIELD NETWORKS - COMPILATION SCRIPT
echo   Version 2.0 - English Interface
echo ========================================

REM Check if source file exists
if not exist "main.cpp" (
    echo Error: main.cpp not found!
    goto :eof
)

REM Remove previous binary if exists
if exist "%EXECUTABLE%.exe" (
    echo Removing previous binary...
    del /q "%EXECUTABLE%.exe" 2>nul
)

REM Compilation
echo Compiling...
%CXX% %CXXFLAGS% -o %EXECUTABLE%.exe main.cpp

REM Check result
if %errorlevel% equ 0 (
    echo Compilation successful!
    echo Ready to run: %EXECUTABLE%.exe
) else (
    echo Compilation failed!
)
```

### Linux/macOS (compile.sh)
```bash
#!/bin/bash
echo "Compiling Hopfield Networks System..."
g++ -std=c++17 -O2 -Wall -Wextra -o hopfield main.cpp
if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    echo "Ready to run: ./hopfield"
else
    echo "Compilation failed!"
    exit 1
fi
```

## Verification Tests

### Test 1: Basic functionality
```bash
# Run program and select option 4 (pattern library)
echo "4" | ./hopfield
```

### Test 2: Pattern addition
```bash
# Run program and add a pattern
echo -e "1\n0\n0\n0\n0\n0\n1\n1\n1\n0\n0\n1\n0\n1\n0\n0\n1\n1\n1\n0\n0\n0\n0\n0\n0\n9" | ./hopfield
```

### Test 3: Pattern search demo
```bash
# Run pattern search demo
echo "5" | ./hopfield
```

### Test 4: System information
```bash
# Check system information
echo "8" | ./hopfield
```

## File Structure After Compilation

```
LLM/
├── main.cpp                    # Source code
├── hopfield.exe                # Executable (Windows)
├── hopfield                    # Executable (Linux/macOS)
├── compile.bat                 # Compilation script
├── patterns.txt                # Pattern file (created automatically)
├── functions_map.json          # Functionality map
├── README.md                   # Main documentation
├── QUICK_START.md              # Quick start guide
├── PROJECT_SUMMARY.md          # Project summary
└── COMPILE_INSTRUCTIONS.md     # This file
```

## New Features in v2.0

### Compilation Script Improvements
- **Automatic cleanup** - Removes previous binary
- **Error checking** - Validates source file and compiler
- **File information** - Shows size and date
- **Interactive option** - Asks if user wants to run program
- **English interface** - All messages in English

### Program Features
- **4 default patterns** - Square, Cross, X, Triangle T
- **English interface** - All text in English
- **Fixed-width formatting** - Better matrix display
- **Enhanced colors** - More visual distinction
- **Row/column numbering** - Better large matrix visualization

## Support

If you encounter compilation issues:
1. Check compiler version: `g++ --version`
2. Check C++17 support: `g++ -std=c++17 --version`
3. Use debug flags: `-g -Wall -Wextra`
4. Check compilation error logs
5. Use the provided compile.bat script for automatic handling

## Quick Start

1. **Compile**: Run `.\compile.bat` (Windows) or `g++ -std=c++17 -O2 -Wall -Wextra -o hopfield main.cpp`
2. **Run**: Execute `.\hopfield.exe` (Windows) or `./hopfield` (Linux/macOS)
3. **Test**: Select option 4 to see pattern library
4. **Explore**: Try all 9 menu options

---

**Ready to compile?** Run `.\compile.bat` and start exploring Hopfield networks!