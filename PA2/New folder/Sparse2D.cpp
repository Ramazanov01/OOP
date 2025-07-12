#include "Sparse2D.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Sparse2D::Sparse2D() {}

// Sparse2D::Sparse2D(const std::string& filename) {
//     std::ifstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Error opening file: " << filename << std::endl;
//         return;
//     }

//     std::string line;
//     while (std::getline(file, line)) {
//         std::istringstream iss(line);
//         int row_index;
//         iss >> row_index;
        
//         int col_index;
//         double value;
//         char separator;
        
//         while (iss >> col_index >> separator >> value) {
//             if (separator == '|' && value != 0.0) {
//                 addEntry(row_index, col_index, value);
//             }
//         }
//     }
// }

Sparse2D::Sparse2D(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Replace non-breaking spaces with regular spaces
        std::replace(line.begin(), line.end(), '\xA0', ' ');
        
        std::istringstream iss(line);
        int row_index;
        iss >> row_index;
        
        int col_index;
        double value;
        char separator;
        
        while (iss >> col_index >> separator >> value) {
            if (separator == '|' && value != 0.0) {
                addEntry(row_index, col_index, value);
            }
        }
    }
}

void Sparse2D::addEntry(int row, int col, double value) {
    auto it = std::lower_bound(row_indices.begin(), row_indices.end(), row);
    size_t pos = it - row_indices.begin();
    
    if (it != row_indices.end() && *it == row) {
        rows[pos].addEntry(col, value);
    } else {
        row_indices.insert(it, row);
        Sparse1D new_row;
        new_row.addEntry(col, value);
        rows.insert(rows.begin() + pos, new_row);
    }
}

Sparse2D Sparse2D::operator+(const Sparse2D& other) const {
    Sparse2D result;
    size_t i = 0, j = 0;
    
    while (i < row_indices.size() && j < other.row_indices.size()) {
        if (row_indices[i] == other.row_indices[j]) {
            Sparse1D merged_row = rows[i] + other.rows[j];
            if (!merged_row.getIndices().empty()) {
                result.row_indices.push_back(row_indices[i]);
                result.rows.push_back(merged_row);
            }
            i++;
            j++;
        } else if (row_indices[i] < other.row_indices[j]) {
            result.row_indices.push_back(row_indices[i]);
            result.rows.push_back(rows[i]);
            i++;
        } else {
            result.row_indices.push_back(other.row_indices[j]);
            result.rows.push_back(other.rows[j]);
            j++;
        }
    }
    
    while (i < row_indices.size()) {
        result.row_indices.push_back(row_indices[i]);
        result.rows.push_back(rows[i]);
        i++;
    }
    
    while (j < other.row_indices.size()) {
        result.row_indices.push_back(other.row_indices[j]);
        result.rows.push_back(other.rows[j]);
        j++;
    }
    
    return result;
}

Sparse2D Sparse2D::operator-(const Sparse2D& other) const {
    Sparse2D result;
    size_t i = 0, j = 0;
    
    while (i < row_indices.size() && j < other.row_indices.size()) {
        if (row_indices[i] == other.row_indices[j]) {
            Sparse1D merged_row = rows[i] - other.rows[j];
            if (!merged_row.getIndices().empty()) {
                result.row_indices.push_back(row_indices[i]);
                result.rows.push_back(merged_row);
            }
            i++;
            j++;
        } else if (row_indices[i] < other.row_indices[j]) {
            result.row_indices.push_back(row_indices[i]);
            result.rows.push_back(rows[i]);
            i++;
        } else {
            result.row_indices.push_back(other.row_indices[j]);
            result.rows.push_back(-other.rows[j]);
            j++;
        }
    }
    
    while (i < row_indices.size()) {
        result.row_indices.push_back(row_indices[i]);
        result.rows.push_back(rows[i]);
        i++;
    }
    
    while (j < other.row_indices.size()) {
        result.row_indices.push_back(other.row_indices[j]);
        result.rows.push_back(-other.rows[j]);
        j++;
    }
    
    return result;
}

Sparse2D Sparse2D::operator-() const {
    Sparse2D result;
    for (size_t i = 0; i < row_indices.size(); i++) {
        result.row_indices.push_back(row_indices[i]);
        result.rows.push_back(-rows[i]);
    }
    return result;
}

Sparse2D Sparse2D::operator*(const Sparse2D& other) const {
    Sparse2D result;
    Sparse2D other_transposed = other.transpose();
    
    for (size_t i = 0; i < row_indices.size(); i++) {
        Sparse1D current_row;
        for (size_t j = 0; j < other_transposed.row_indices.size(); j++) {
            double dot_product = rows[i].dot(other_transposed.rows[j]);
            if (dot_product != 0.0) {
                current_row.addEntry(other_transposed.row_indices[j], dot_product);
            }
        }
        if (!current_row.getIndices().empty()) {
            result.row_indices.push_back(row_indices[i]);
            result.rows.push_back(current_row);
        }
    }
    return result;
}

Sparse2D Sparse2D::transpose() const {
    Sparse2D result;
    for (size_t i = 0; i < row_indices.size(); i++) {
        const Sparse1D& current_row = rows[i];
        const std::vector<int>& cols = current_row.getIndices();
        const std::vector<double>& vals = current_row.getValues();
        
        for (size_t j = 0; j < cols.size(); j++) {
            result.addEntry(cols[j], row_indices[i], vals[j]);
        }
    }
    return result;
}

Sparse1D& Sparse2D::row(int row_index) {
    auto it = std::lower_bound(row_indices.begin(), row_indices.end(), row_index);
    if (it != row_indices.end() && *it == row_index) {
        return rows[it - row_indices.begin()];
    }
    throw std::out_of_range("Row index not found");
}

Sparse1D Sparse2D::column(int column_index) const {
    Sparse1D result;
    for (size_t i = 0; i < row_indices.size(); i++) {
        double val = rows[i].getValue(column_index);
        if (val != 0.0) {
            result.addEntry(row_indices[i], val);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Sparse2D& sm) {
    for (size_t i = 0; i < sm.row_indices.size(); i++) {
        os << sm.row_indices[i] << " " << sm.rows[i] << "\n";
    }
    return os;
}