#ifndef SPARSE2D_H
#define SPARSE2D_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>  // for atoi, atof
#include "Sparse1D.h"

using namespace std;

class Sparse2D
{
private:
    // The row indices (actual row numbers)
    vector<int> row_indices;
    // Stores the content of each row as Sparse1D
    vector<Sparse1D> data;

    // Helper function: sorts row_indices and data together based on row_indices using bubble sort
    void bubbleSortByRowIndex();

public:
    // 1) Default constructor: Creates an empty Sparse2D
    Sparse2D();

    // 2) Constructor that reads from file:
    // Each line must be in the format:
    // rowIndex  col1|val1  col2|val2  ...
    // Example: "3 3|24.6 4|5.5"
    Sparse2D(const string &filename);

    // 3) operator+ : Adds two matrices (row-based)
    Sparse2D operator+(const Sparse2D &other) const;

    // 4) operator- : Subtracts one matrix from another (row-based)
    Sparse2D operator-(const Sparse2D &other) const;

    // 5) operator- : Unary minus (negates all elements in the matrix)
    Sparse2D operator-() const;

    // 6) operator<< : Outputs the matrix; format:
    //    row_index col|val col|val ...
    friend ostream& operator<<(ostream &os, const Sparse2D &obj);

    // 7) operator* : Multiplies two matrices (classic matrix multiplication)
    Sparse2D operator*(const Sparse2D &other) const;

    // 8) transpose() : Returns the transpose of the matrix (swaps rows and columns)
    Sparse2D transpose() const;

    // 9) row(int row_index) : Returns a reference to a specific row as a Sparse1D object.
    //    If not found,exit.
    Sparse1D& row(int row_index);

    // 10) column(int column_index) : Returns a specific column as a Sparse1D object (by value)
    Sparse1D column(int column_index) const;
};

#endif // SPARSE2D_H
