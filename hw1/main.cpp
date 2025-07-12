#include "AnsiTerminal.h"
#include "Spreadsheet.h"
#include <iostream>

int main() {
    AnsiTerminal terminal;
    terminal.clearScreen(); // Clear the screen at the beginning

    Spreadsheet sheet(10, 10);
    sheet.setCellValue("A1", "5");
    sheet.setCellValue("B1", "10");
    sheet.setCellValue("C1", "=A1 + B1");
    sheet.calculateCell("C1");

    int row = 1, col = 1;
    terminal.printInvertedAt(row, col, "*"); // Initial cursor position in inverted mode

    char key;
    while (true) {
        key = terminal.getSpecialKey();

        // Clear the previous position
        terminal.printAt(row, col, " ");

        // Display the cell value at the previous position
        std::string cellName = std::string(1, 'A' + (col - 1)) + std::to_string(row);
        std::string cellValue = sheet.getCellValue(cellName);
        if (!cellValue.empty()) {
            terminal.printAt(row, col, cellValue);
        }

        // Update position based on key input
        switch (key) {
            case 'U': row = (row > 1) ? row - 1 : row; break; // Up (W)
            case 'D': row = (row < 10) ? row + 1 : row; break; // Down (S)
            case 'R': col = (col < 10) ? col + 1 : col; break; // Right (D)
            case 'L': col = (col > 1) ? col - 1 : col; break; // Left (A)
            case 'Q': return 0; // Quit program if 'q' is pressed
        }

        // Display inverted cursor at new position
        terminal.printInvertedAt(row, col, "*");
    }

    terminal.clearScreen(); // Clear the screen on exit
    return 0;
}
