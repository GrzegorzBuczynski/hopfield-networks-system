@echo off
setlocal enabledelayedexpansion

REM ========================================
REM Hopfield Networks - Compilation Script
REM Version 2.0 - English Interface
REM ========================================

set "EXECUTABLE=hopfield"
set "CXX=g++"
set "CXXFLAGS=-std=c++17 -O2 -Wall -Wextra"
set "LDFLAGS="

echo.
echo ========================================
echo   HOPFIELD NETWORKS - COMPILATION SCRIPT
echo   Version 2.0 - English Interface
echo ========================================
echo.
echo Compiler: %CXX%
echo Flags: %CXXFLAGS%
echo Executable: %EXECUTABLE%.exe
echo.

REM Check if source file exists
if not exist "main.cpp" (
    echo Error: main.cpp not found!
    echo Please ensure main.cpp is in the current directory.
    goto :eof
)

REM Remove previous binary if exists
if exist "%EXECUTABLE%.exe" (
    echo Removing previous binary...
    del /q "%EXECUTABLE%.exe" 2>nul
    if exist "%EXECUTABLE%.exe" (
        echo Warning: Cannot remove previous binary (may be in use)
        echo Please close any running instances and try again.
        goto :eof
    ) else (
        echo Previous binary removed
    )
)

REM Check compiler availability
where %CXX% >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: Compiler %CXX% not found!
    echo Please install MinGW or set CXX environment variable.
    echo Download MinGW from: https://www.mingw-w64.org/
    goto :eof
)

REM Compilation
echo Compiling...
%CXX% %CXXFLAGS% -o %EXECUTABLE%.exe main.cpp %LDFLAGS%

REM Check compilation result
if %errorlevel% equ 0 (
    echo.
    echo Compilation successful!
    echo Executable: %EXECUTABLE%.exe
    
    REM Show file information
    if exist "%EXECUTABLE%.exe" (
        echo.
        echo File information:
        for %%F in ("%EXECUTABLE%.exe") do (
            echo Size: %%~zF bytes
            echo Date: %%~tF
        )
        echo.
        echo Ready to run: %EXECUTABLE%.exe
        echo Quick test: echo "4" ^| .\%EXECUTABLE%.exe
    )
) else (
    echo.
    echo Compilation failed!
    echo.
    echo Attempting compilation with error display:
    %CXX% %CXXFLAGS% -o %EXECUTABLE%.exe main.cpp %LDFLAGS%
    echo.
    echo Please fix the errors above and try again.
)

echo.
echo ========================================
echo   COMPILATION COMPLETED
echo ========================================
echo.

REM Optional: Ask if user wants to run the program
set /p "choice=Run the program now? (y/N): "
if /i "!choice!"=="y" (
    echo.
    echo Starting %EXECUTABLE%.exe...
    echo.
    %EXECUTABLE%.exe
)

echo.
echo Thank you for using Hopfield Networks!