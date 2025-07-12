#include "Spreadsheet.h"
#include <iostream>
#include <fstream>
#include <sstream>

Spreadsheet::Spreadsheet(int rows, int cols) {
    cells.resize(rows, std::vector<Cell>(cols));
}

std::pair<int, int> Spreadsheet::getCellPosition(const std::string& cellName) {
    if (cellMap.find(cellName) != cellMap.end()) {
        return cellMap[cellName];
    }
    int col = cellName[0] - 'A';
    int row = std::stoi(cellName.substr(1)) - 1;
    cellMap[cellName] = {row, col};
    return {row, col};
}

double Spreadsheet::evaluateExpression(const std::string& expr) {
    std::istringstream iss(expr);
    std::string token;
    double result = 0;
    char op = '+';
    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            op = token[0];
        } else {
            double value = 0;
            if (isalpha(token[0])) {
                auto pos = getCellPosition(token);
                value = std::stod(cells[pos.first][pos.second].value);
            } else {
                value = std::stod(token);
            }
            switch (op) {
                case '+': result += value; break;
                case '-': result -= value; break;
                case '*': result *= value; break;
                case '/': result /= value; break;
            }
        }
    }
    return result;
}

void Spreadsheet::setCellValue(const std::string& cellName, const std::string& value) {
    auto pos = getCellPosition(cellName);
    cells[pos.first][pos.second].value = value;
}

std::string Spreadsheet::getCellValue(const std::string& cellName) {
    auto pos = getCellPosition(cellName);
    return cells[pos.first][pos.second].value;
}

void Spreadsheet::calculateCell(const std::string& cellName) {
    auto pos = getCellPosition(cellName);
    std::string value = cells[pos.first][pos.second].value;
    if (value[0] == '=') {
        std::string expr = value.substr(1);
        double result = evaluateExpression(expr);
        cells[pos.first][pos.second].value = std::to_string(result);
    }
}

void Spreadsheet::printSpreadsheet() {
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            std::cout << cell.value << "\t";
        }
        std::cout << std::endl;
    }
}

void Spreadsheet::saveToCSV(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& row : cells) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i].value;
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}

void Spreadsheet::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string value;
        int col = 0;
        while (std::getline(iss, value, ',')) {
            cells[row][col].value = value;
            ++col;
        }
        ++row;
    }
}
