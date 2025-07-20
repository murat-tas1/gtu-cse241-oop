#ifndef SPARSE1D_H
#define SPARSE1D_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>  // for atoi, atof

using namespace std;

class Sparse1D
{
  friend class Sparse2D;

private:
    vector<int> indices;     // Holds the index positions of non-zero elements
    vector<double> data;     // Holds the corresponding non-zero values

    // Bubble sort helper to keep (indices, data) in ascending order of indices
    void bubbleSortByIndex();

public:
    // Default constructor
    Sparse1D();

    // Constructor that reads from a file (e.g. "4|23.8 7|10.7 ...")
    // and only stores non-zero values
    Sparse1D(const string &filename);

    // Operator + : element-wise addition
    Sparse1D operator+(const Sparse1D &other) const;

    // Operator - (binary): element-wise subtraction
    Sparse1D operator-(const Sparse1D &other) const;

    // Operator - (unary): negates each value
    Sparse1D operator-() const;

    // Dot product
    double dot(const Sparse1D &other) const;

    // For printing: index|value index|value ...
    friend ostream &operator<<(ostream &os, const Sparse1D &obj);
};

#endif // SPARSE1D_H
