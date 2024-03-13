# Matrix Library Documentation

# Summary
A include file for fast matrix manipulations like operators, transpose, identity and Gauss-Jordan

## Overview
The Matrix library provides a comprehensive toolkit for matrix operations in C++. It supports matrices of any size and type, with operations that include matrix construction, element access, arithmetic operations, comparisons, and advanced operations like transposing, finding the inverse, and solving linear systems.

### Compilation
Use this command to run the code

- g++ *.cpp -L /usr/lib/boost -o main -std=c++17 -lboost_unit_test_framework -Wall -g -o main

## File Information
- **File Name:** Matrix.inc
- **Description:** Implementation file for the Matrix class template.
- **Author:** SHG Selten
- **Date:** 13-03-2024
- **Version:** 1.0

## Dependencies
The library utilizes standard C++ headers to ensure functionality and reliability across various operations:
- `<cassert>`: For internal assertions to validate function preconditions.
- `<stdexcept>`: To throw exceptions in cases of invalid operations or arguments.
- `<cmath>`: For mathematical operations necessary in matrix computations.
- `<utility>`: For utility functions such as `std::swap` used in matrix row operations.

## Template Parameters
- `T`: The type of elements stored in the matrix (e.g., `int`, `float`, `double`).
- `M`: The number of rows in the matrix.
- `N`: The number of columns in the matrix.

## Core Features
- **Construction**: Initialize matrices with specific dimensions and values, or via initializer lists for both single and nested lists.
- **Element Access**: Direct access to matrix elements for both const and non-const instances.
- **Arithmetic Operations**: Includes addition, subtraction, multiplication, and division with both scalars and other matrices.
- **Comparisons**: Supports equality checks between matrices.
- **Advanced Operations**: Transposing, finding the inverse, performing Gaussian elimination, Gauss-Jordan elimination, and solving linear equations.

## Usage Examples
The Matrix library is designed to be intuitive for users familiar with basic C++ syntax and template usage. Here are a few examples of how to use some of the core features:

### Constructing a Matrix
```cpp
Matrix<int, 2, 3> mat1(0); // A 2x3 matrix of ints, initialized to 0.
Matrix<double, 3, 3> mat2{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}; // 3x3 identity matrix.
```

### Perfoming Operations
```cpp
auto mat3 = mat1 + mat2; // Assuming mat1 and mat2 are of compatible dimensions.
mat1 *= 2; // Multiply all elements of mat1 by 2.
```

### Advanced Features
```cpp
auto transposed = mat2.transpose();
auto inverse = mat2.inverse();
```
