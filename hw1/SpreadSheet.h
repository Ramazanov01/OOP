#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <vector>
#include <string>
#include <unordered_map>

class Cell {
public:
    std::string value;
    Cell() : value("") {}
};

class Spreadsheet {
private:
    std::vector<std::vector<Cell>> cells;
    std::unordered_map<std::string, std::pair<int, int>> cellMap;

    std::pair<int, int> getCellPosition(const std::string& cellName);
    double evaluateExpression(const std::string& expr);

public:
    Spreadsheet(int rows, int cols);
    void setCellValue(const std::string& cellName, const std::string& value);
    std::string getCellValue(const std::string& cellName);
    void calculateCell(const std::string& cellName);
    void printSpreadsheet();
    void saveToCSV(const std::string& filename);
    void loadFromCSV(const std::string& filename);
};

#endif // SPREADSHEET_H
