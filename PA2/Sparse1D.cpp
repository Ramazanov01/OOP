#include "Sparse1D.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Sparse1D::Sparse1D() {}

Sparse1D::Sparse1D(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int index;
        double value;
        char separator;
        
        while (iss >> index >> separator >> value) {
            if (separator == '|' && value != 0.0) {
                addEntry(index, value);
            }
        }
    }
}

void Sparse1D::addEntry(int index, double value) {
    auto it = std::lower_bound(indices.begin(), indices.end(), index);
    size_t pos = it - indices.begin();
    
    if (it != indices.end() && *it == index) {
        values[pos] = value;
    } else {
        indices.insert(it, index);
        values.insert(values.begin() + pos, value);
    }
}

Sparse1D Sparse1D::operator+(const Sparse1D& other) const {
    Sparse1D result;
    size_t i = 0, j = 0;
    
    while (i < indices.size() && j < other.indices.size()) {
        if (indices[i] == other.indices[j]) {
            double sum = values[i] + other.values[j];
            if (sum != 0.0) {
                result.addEntry(indices[i], sum);
            }
            i++;
            j++;
        } else if (indices[i] < other.indices[j]) {
            result.addEntry(indices[i], values[i]);
            i++;
        } else {
            result.addEntry(other.indices[j], other.values[j]);
            j++;
        }
    }
    
    while (i < indices.size()) {
        result.addEntry(indices[i], values[i]);
        i++;
    }
    
    while (j < other.indices.size()) {
        result.addEntry(other.indices[j], other.values[j]);
        j++;
    }
    
    return result;
}

Sparse1D Sparse1D::operator-(const Sparse1D& other) const {
    Sparse1D result;
    size_t i = 0, j = 0;
    
    while (i < indices.size() && j < other.indices.size()) {
        if (indices[i] == other.indices[j]) {
            double diff = values[i] - other.values[j];
            if (diff != 0.0) {
                result.addEntry(indices[i], diff);
            }
            i++;
            j++;
        } else if (indices[i] < other.indices[j]) {
            result.addEntry(indices[i], values[i]);
            i++;
        } else {
            result.addEntry(other.indices[j], -other.values[j]);
            j++;
        }
    }
    
    while (i < indices.size()) {
        result.addEntry(indices[i], values[i]);
        i++;
    }
    
    while (j < other.indices.size()) {
        result.addEntry(other.indices[j], -other.values[j]);
        j++;
    }
    
    return result;
}

Sparse1D Sparse1D::operator-() const {
    Sparse1D result;
    for (size_t i = 0; i < indices.size(); i++) {
        result.addEntry(indices[i], -values[i]);
    }
    return result;
}

Sparse1D& Sparse1D::operator=(const Sparse1D& other) {
    if (this != &other) {
        indices = other.indices;
        values = other.values;
    }
    return *this;
}

double Sparse1D::dot(const Sparse1D& other) const {
    double sum = 0.0;
    size_t i = 0, j = 0;
    
    while (i < indices.size() && j < other.indices.size()) {
        if (indices[i] == other.indices[j]) {
            sum += values[i] * other.values[j];
            i++;
            j++;
        } else if (indices[i] < other.indices[j]) {
            i++;
        } else {
            j++;
        }
    }
    return sum;
}

double Sparse1D::getValue(int index) const {
    auto it = std::lower_bound(indices.begin(), indices.end(), index);
    if (it != indices.end() && *it == index) {
        return values[it - indices.begin()];
    }
    return 0.0;
}

std::ostream& operator<<(std::ostream& os, const Sparse1D& sv) {
    for (size_t i = 0; i < sv.indices.size(); i++) {
        os << sv.indices[i] << "|" << sv.values[i];
        if (i != sv.indices.size() - 1) {
            os << " ";
        }
    }
    return os;
}