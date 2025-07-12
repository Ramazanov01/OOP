#ifndef SPARSE1D_H
#define SPARSE1D_H

#include <iostream>
#include <vector>
#include <string>

class Sparse1D {
public:
    Sparse1D();
    Sparse1D(const std::string& filename);
    Sparse1D(const Sparse1D& other) = default;  // Default copy constructor
    
    // Basic operations
    Sparse1D operator+(const Sparse1D& other) const;
    Sparse1D operator-(const Sparse1D& other) const;
    Sparse1D operator-() const;
    Sparse1D& operator=(const Sparse1D& other);
    
    // Dot product
    double dot(const Sparse1D& other) const;
    
    // Output
    friend std::ostream& operator<<(std::ostream& os, const Sparse1D& sv);
    
    // Accessors
    const std::vector<int>& getIndices() const { return indices; }
    const std::vector<double>& getValues() const { return values; }
    double getValue(int index) const;
    void addEntry(int index, double value);

private:
    std::vector<int> indices;
    std::vector<double> values;
    
    
};

#endif // SPARSE1D_H