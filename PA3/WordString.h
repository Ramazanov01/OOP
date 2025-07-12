 #ifndef WORDSTRING_H
 #define WORDSTRING_H
 
 #include <iostream>
 #include <cstring>
 
 class WordString {
 private:
     char** words;          // Dynamic array of C-string words
     int* spaces;           // Number of spaces after each word
     int wordCount;         // Total number of words in the string
     
     // Helper functions
     void tokenize(const char* input);  // Parse input string into words and spaces
     void cleanup();                    // Free dynamically allocated memory
     void copy(const WordString& other); // Deep copy from another WordString
     bool isSpace(char c) const;        // Check if character is a space
     
 public:
     // Constructors and destructor
     WordString();                       // Default constructor
     WordString(const char* input);      // Constructor from C-string
     WordString(const std::string& input); // Constructor from std::string
     WordString(const WordString& other); // Copy constructor
     ~WordString();                      // Destructor
     
     // Operators
     WordString& operator=(const WordString& other); // Assignment operator
     bool operator==(const WordString& other) const; // Equality operator
     WordString operator+(const WordString& other) const; // Concatenation operator
     WordString operator+(const std::string& other) const; // Concatenation with std::string
     WordString operator+(const char* other) const; // Concatenation with C-string
     
     // Stream operators (declared as friends for direct access to private members)
     friend std::ostream& operator<<(std::ostream& os, const WordString& ws);
     friend std::istream& operator>>(std::istream& is, WordString& ws);
     
     // Word manipulation functions
     std::string get(int index) const;    // Get word at specified index
     void replace(int index, const std::string& newWord); // Replace word at index
     void insertAfter(int index, const std::string& text); // Insert text after word at index
     void insertBefore(int index, const std::string& text); // Insert text before word at index
     void remove(int index);             // Remove word at specified index
     void strip();                       // Remove excessive spaces
     
     // Utility functions
     int numberOfWords() const;          // Return number of words
     std::string toString() const;       // Convert to std::string
     
     // Debug function
     void printDetails() const;          // Print internal structure details (for debugging)
 };
 
 #endif // WORDSTRING_H