// #include <iostream>
// #include <fstream>
// #include "Sparse1D.h"
// #include "Sparse2D.h"

// int main() {
//     std::ofstream out("output.txt");

//     // Test Sparse1D
//     Sparse1D a1("a1.txt");
//     //Sparse1D bl("bl.txt");

//     out << "a1: " << a1 << std::endl;
//     //out << "bl: " << bl << std::endl;
//     out << "a1 + a1: " << a1 + a1 << std::endl;
//     //out << "al - bl: " << al - bl << std::endl;
//     out << "Dot product (a1 • -): " << a1.dot(-a1) << std::endl;

//     // Test Sparse2D
//     Sparse2D ml("m1.txt");
//     Sparse2D m2("m2.txt");

//     out << "ml:\n" << ml << std::endl;
//     out << "m2:\n" << m2 << std::endl;
//     out << "ml + m2:\n" << ml + m2 << std::endl;
//     out << "m2 transpose:\n" << m2.transpose() << std::endl;
//     out << "Column 5 of m2:\n" << Sparse2D("m2.txt").column(5) << std::endl;

//     return 0;
// }

#include <iostream>
#include <fstream>
#include "Sparse1D.h"
#include "Sparse2D.h"

void testSparse1D(std::ostream& out) {
    out << "\n=== TESTING SPARSE1D ===\n";

    // Test constructors and file loading
    Sparse1D a1("a1.txt");
    Sparse1D empty;
    
    out << "a1: " << a1 << std::endl;
    out << "empty: " << empty << std::endl;

    // Test basic operations
    out << "a1 + a1: " << a1 + a1 << std::endl;
    out << "a1 - a1: " << a1 - a1 << std::endl;
    out << "-a1: " << -a1 << std::endl;

    // Test dot product
    out << "Dot product (a1 • a1): " << a1.dot(a1) << std::endl;
    out << "Dot product (a1 • -a1): " << a1.dot(-a1) << std::endl;

    // Test value access
    out << "Value at index 4: " << a1.getValue(4) << std::endl;
    out << "Value at index 999: " << a1.getValue(999) << std::endl;

    // Test adding entries
    Sparse1D manual;
    manual.addEntry(1, 2.5);
    manual.addEntry(3, 4.5);
    manual.addEntry(1, 3.5); // Should update existing entry
    out << "Manual: " << manual << std::endl;
}

void testSparse2D(std::ostream& out) {
    out << "\n=== TESTING SPARSE2D ===\n";

    // Test constructors and file loading
    Sparse2D m1("m1.txt");
    Sparse2D m2("m2.txt");
    Sparse2D empty;
    
    out << "m1:\n" << m1 << std::endl;
    out << "m2:\n" << m2 << std::endl;
    out << "empty:\n" << empty << std::endl;

    // Test basic operations
    out << "m1 + m2:\n" << m1 + m2 << std::endl;
    out << "m1 - m2:\n" << m1 - m2 << std::endl;
    out << "-m1:\n" << -m1 << std::endl;

    // Test matrix multiplication
    out << "m1 * m2 (matrix multiplication):\n" << m1 * m2 << std::endl;

    // Test transpose
    out << "m1 transpose:\n" << m1.transpose() << std::endl;
    out << "m2 transpose:\n" << m2.transpose() << std::endl;

    // Test row and column access
    try {
        out << "Row 9 of m1: " << m1.row(9) << std::endl;
        out << "Row 999 of m1: "; // Should throw exception
        out << m1.row(999) << std::endl;
    } catch (const std::out_of_range& e) {
        out << "Exception: " << e.what() << std::endl;
    }

    out << "Column 5 of m1:\n" << m1.column(5) << std::endl;
    out << "Column 1 of m2:\n" << m2.column(1) << std::endl;
    out << "Column 999 of m2:\n" << m2.column(999) << std::endl;

    // Test adding entries
    Sparse2D manual;
    manual.addEntry(1, 1, 2.5);
    manual.addEntry(1, 2, 3.5);
    manual.addEntry(2, 1, 4.5);
    manual.addEntry(1, 1, 5.5); // Should update existing entry
    out << "Manual:\n" << manual << std::endl;
}

void additionalTests(std::ostream& out) {
    out << "\n=== ADDITIONAL TESTS ===\n";

    // Test with empty matrices
    Sparse1D s1;
    Sparse1D s2;
    out << "Empty + Empty: " << s1 + s2 << std::endl;
    out << "Empty - Empty: " << s1 - s2 << std::endl;
    out << "Empty dot Empty: " << s1.dot(s2) << std::endl;

    Sparse2D sm1;
    Sparse2D sm2;
    out << "Empty 2D + Empty 2D:\n" << sm1 + sm2 << std::endl;
    out << "Empty 2D * Empty 2D:\n" << sm1 * sm2 << std::endl;

    // Test edge cases
    Sparse1D edge1;
    edge1.addEntry(0, 0.0); // Shouldn't be added (0 value)
    edge1.addEntry(1, 1e-10);
    edge1.addEntry(2, -1e-10);
    out << "Edge case 1D: " << edge1 << std::endl;

    Sparse2D edge2;
    edge2.addEntry(0, 0, 0.0); // Shouldn't be added
    edge2.addEntry(1, 1, 1e-10);
    edge2.addEntry(2, 2, -1e-10);
    out << "Edge case 2D:\n" << edge2 << std::endl;
}

int main() {
    std::ofstream out("output.txt");

    out << "=== SPARSE MATRIX TEST SUITE ===\n";
    
    testSparse1D(out);
    testSparse2D(out);
    additionalTests(out);

    out << "\n=== TESTS COMPLETED ===\n";
    std::cout << "All tests completed. Results written to output.txt\n";

    return 0;
}