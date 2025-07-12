#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>


// Field class to hold the details of each field in the schema
class Field {
public:
    std::string name;
    std::string type;
    bool isArray;

    // Constructor to initialize a Field object
    Field(const std::string &n, const std::string &t, const std::string &ia);
};

// Record class to hold the details of each record
class Record {
public:
    std::map<std::string, std::vector<std::string>> fields; // Map to hold field values

    // Function to format a record according to the schema
    std::string getFormattedRecord(const std::vector<Field> &schema) const;

    // Function to join a vector of strings with a delimiter
    static std::string join(const std::vector<std::string> &vec, const std::string &delim);
};

// CatalogManager class to manage the catalog operations
class CatalogManager {
private:
    std::vector<Field> schema; // Vector to hold the schema fields
    std::vector<Record> records; // Vector to hold the records
    std::set<std::string> uniqueEntries; // Set to ensure unique entries
    std::ofstream logFile; // Log file stream

    // Function to log exceptions to the log file
    void logException(const std::string &message);

    // Helper function to trim spaces and quotes from a string
    std::string trim(const std::string &str);

    // Function to check if a field exists in the schema
    bool fieldExists(const std::string &fieldName);

    // Helper function to get quoted string from input stream
    std::string getQuotedString(std::istringstream &ss);

public:
    // Constructor to open the log file
    CatalogManager();

    // Destructor to close the log file
    ~CatalogManager();

    // Function to parse the catalog from the given file
    void parseCatalog(const std::string &filename);

    // Function to process commands from the given file
    void processCommands(const std::string &filename);

    // Function to search for a value in a given field
    void search(const std::string &fieldName, const std::string &value);

    // Function to sort records by a given field
    void sort(const std::string &fieldName);
};

#endif // CATALOGMANAGER_H
