#ifndef SPARSE2D_H
#define SPARSE2D_H

#include "Sparse1D.h"
#include <vector>
#include <iostream>

class Sparse2D {
public:
    Sparse2D();
    Sparse2D(const std::string& filename);
    
    // Matrix operations
    Sparse2D operator+(const Sparse2D& other) const;
    Sparse2D operator-(const Sparse2D& other) const;
    Sparse2D operator-() const;
    Sparse2D operator*(const Sparse2D& other) const;
    Sparse2D transpose() const;
    
    // Accessors
    Sparse1D& row(int row_index);
    Sparse1D column(int column_index) const;
    
    // Output
    friend std::ostream& operator<<(std::ostream& os, const Sparse2D& sm);
    void addEntry(int row, int col, double value);

private:
    std::vector<int> row_indices;
    std::vector<Sparse1D> rows;
    
};

#endif // SPARSE2D_H