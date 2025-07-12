#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

// Include necessary standard libraries
#include <iostream>         // For input/output stream operations
#include <fstream>          // For file read/write operations
#include <sstream>          // For string stream parsing
#include <vector>           // For dynamic array structures
#include <set>              // For checking unique entries
#include <algorithm>        // For algorithms like transform, sort, etc.
#include <iterator>         // For iterators (not used directly)
#include <stdexcept>        // For throwing runtime and custom errors
#include <memory>           // For smart pointers like shared_ptr

// Enumeration for field data types (string, integer, double, boolean)
enum class DataType {
    String,
    Integer,
    Double,
    Bool
};

// Enumeration for field multiplicity (single value or multiple values)
enum class FieldType {
    Single,
    Multi
};

// Class to represent the format of a field (name, type, multiplicity)
class FieldFormat {
public:
    std::string name;       // Name of the field
    DataType type;          // Data type of the field
    FieldType multiplicity; // Whether the field holds single or multiple values

    // Constructor to initialize the field format
    FieldFormat(const std::string& n, const std::string& t, const std::string& multi)
        : name(n) {
        // Convert string representation of type to DataType enum
        if (t == "string") type = DataType::String;
        else if (t == "integer") type = DataType::Integer;
        else if (t == "double") type = DataType::Double;
        else if (t == "bool") type = DataType::Bool;
        else throw std::runtime_error("Invalid field type: " + t);

        // Set multiplicity based on input
        multiplicity = (multi == "multi") ? FieldType::Multi : FieldType::Single;
    }
};

// Base class for field data, providing common interface
class FieldBase {
public:
    virtual ~FieldBase() = default;
    virtual FieldType getType() const = 0;       // Returns the field multiplicity type
    virtual std::string toString() const = 0;    // Converts field data to string
};

// Template class for single-value fields
template<typename T>
class FieldSingle : public FieldBase {
private:
    T data; // The single value stored in the field
public:
    explicit FieldSingle(T value) : data(std::move(value)) {}
    T getData() const { return data; } // Getter for the stored value
    FieldType getType() const override { return FieldType::Single; }
    std::string toString() const override {
        std::ostringstream ss;
        if constexpr (std::is_same<T, bool>::value) {
            ss << (data ? "true" : "false"); // Special handling for boolean values
        } else {
            ss << data; // Direct output for other types
        }
        return ss.str();
    }
};

// Template class for multi-value fields
template<typename T>
class FieldMulti : public FieldBase {
private:
    std::vector<T> data; // Vector to store multiple values
public:
    explicit FieldMulti(std::vector<T> values) : data(std::move(values)) {}
    const std::vector<T>& getData() const { return data; } // Getter for all values
    T getData(size_t index) const {
        if (index >= data.size()) throw std::out_of_range("Index out of range");
        return data[index]; // Getter for a specific value by index
    }
    size_t getSize() const { return data.size(); } // Returns the number of values
    FieldType getType() const override { return FieldType::Multi; }
    std::string toString() const override {
        std::ostringstream ss;
        for (size_t i = 0; i < data.size(); ++i) {
            if constexpr (std::is_same<T, bool>::value) {
                ss << (data[i] ? "true" : "false"); // Special handling for boolean values
            } else {
                ss << data[i]; // Direct output for other types
            }
            if (i < data.size() - 1) ss << ":"; // Separate values with colons
        }
        return ss.str();
    }
};

// Class to represent an entry (row) in the catalog
class Entry {
public:
    std::vector<std::shared_ptr<FieldBase>> fields; // Fields in the entry
    std::string getFormattedEntry(const std::vector<FieldFormat>& schema) const; // Formats the entry as a string
};

// Exception class for missing fields in an entry
class MissingFieldException : public std::exception {
private:
    std::string message;
public:
    explicit MissingFieldException(const std::string& line)
        : message("Exception: missing field\n" + line) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Exception class for duplicate entries in the catalog
class DuplicateEntryException : public std::exception {
private:
    std::string message;
public:
    explicit DuplicateEntryException(const std::string& line)
        : message("Exception: duplicate entry\n" + line) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Exception class for invalid commands
class WrongCommandException : public std::exception {
private:
    std::string message;
public:
    explicit WrongCommandException()
        : message("Exception: command is wrong") {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Template function to parse a string value into a specified type
template<typename T>
T parseValue(const std::string& value);

// Specialization for parsing string values
template<>
inline std::string parseValue<std::string>(const std::string& value) {
    if (value.empty()) throw std::runtime_error("Empty string value");
    return value;
}

// Specialization for parsing integer values
template<>
inline int parseValue<int>(const std::string& value) {
    if (value.empty()) throw std::runtime_error("Empty int value");
    return std::stoi(value);
}

// Specialization for parsing double values
template<>
inline double parseValue<double>(const std::string& value) {
    if (value.empty()) throw std::runtime_error("Empty double value");
    return std::stod(value);
}

// Specialization for parsing boolean values
template<>
inline bool parseValue<bool>(const std::string& value) {
    if (value.empty()) throw std::runtime_error("Empty bool value");
    std::string lower = value;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return (lower == "true" || lower == "1");
}

// Main class for managing the catalog (parsing, searching, sorting)
class CatalogManager {
private:
    std::vector<FieldFormat> schema;     // Schema defining the fields
    std::vector<Entry> entries;          // List of entries in the catalog
    std::set<std::string> uniqueEntries; // Set to ensure entry uniqueness
    std::ofstream logFile;               // File stream for logging

    // Helper methods
    std::string trim(const std::string& str); // Trims whitespace and quotes from a string
    bool fieldExists(const std::string& fieldName); // Checks if a field exists in the schema
    std::string getQuotedString(std::istringstream& ss); // Extracts a quoted string from a stream
    void logException(const std::string& message); // Logs exceptions to the log file
    int getFieldIndex(const std::string& fieldName); // Gets the index of a field in the schema

public:
    CatalogManager();  // Constructor
    ~CatalogManager(); // Destructor

    // Public interface methods
    void parseCatalog(const std::string& filename); // Parses the catalog file
    void processCommands(const std::string& filename); // Processes commands from a file
    void search(const std::string& fieldName, const std::string& value); // Searches for entries
    void sort(const std::string& fieldName); // Sorts entries by a field
};

#endif // CATALOGMANAGER_H