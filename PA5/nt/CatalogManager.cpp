#include "CatalogManager.h"
#include <cctype>

// Returns a formatted string representation of the entry based on the schema
std::string Entry::getFormattedEntry(const std::vector<FieldFormat>& schema) const {
    std::stringstream entryStream;
    for (size_t i = 0; i < schema.size(); ++i) {
        if (i < fields.size() && fields[i]) {
            entryStream << fields[i]->toString(); // Append field value
        }
        if (i < schema.size() - 1) {
            entryStream << "|"; // Separate fields with pipes
        }
    }
    return entryStream.str();
}

// Constructor: Opens the log file for writing
CatalogManager::CatalogManager() {
    logFile.open("output.txt");
    if (!logFile.is_open()) {
        throw std::runtime_error("Log file could not be opened.");
    }
}

// Destructor: Closes the log file if it's open
CatalogManager::~CatalogManager() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

// Logs an exception message to the log file
void CatalogManager::logException(const std::string& message) {
    logFile << message << std::endl;
}

// Trims whitespace and quotes from a string
std::string CatalogManager::trim(const std::string& str) {
    if (str.empty()) return str;
    size_t first = str.find_first_not_of(" \t\n\r\"");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r\"");
    return str.substr(first, last - first + 1);
}

// Checks if a field exists in the schema
bool CatalogManager::fieldExists(const std::string& fieldName) {
    std::string trimmedName = trim(fieldName);
    return std::any_of(schema.begin(), schema.end(), 
        [&trimmedName](const FieldFormat& field) {
            return field.name == trimmedName;
        });
}

// Returns the index of a field in the schema, or -1 if not found
int CatalogManager::getFieldIndex(const std::string& fieldName) {
    std::string trimmedName = trim(fieldName);
    for (size_t i = 0; i < schema.size(); ++i) {
        if (schema[i].name == trimmedName) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Extracts a quoted string from a stream (handles both quoted and unquoted strings)
std::string CatalogManager::getQuotedString(std::istringstream& ss) {
    ss >> std::ws;
    std::string result;
    if (ss.peek() == '"') {
        ss.get();
        char ch;
        while (ss.get(ch) && ch != '"') {
            result += ch;
        }
    } else {
        ss >> result;
    }
    return trim(result);
}

// Parses the catalog file and populates the schema and entries
void CatalogManager::parseCatalog(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Data file could not be opened.");
    }

    std::string line;
    int uniqueCount = 0;
    if (getline(file, line)) {
        std::istringstream ss(line);
        std::string fieldDef;
        std::vector<std::string> fieldNames;

        // Parse the schema line (field definitions)
        while (getline(ss, fieldDef, '|')) {
            std::istringstream fieldSS(fieldDef);
            std::string fieldName, fieldType, fieldMulti;
            getline(fieldSS, fieldName, ':');
            getline(fieldSS, fieldType, ':');
            getline(fieldSS, fieldMulti);
            schema.emplace_back(fieldName, fieldType, fieldMulti); // Add to schema
            fieldNames.push_back(fieldName);
        }

        // Log the field names
        for (size_t i = 0; i < fieldNames.size(); ++i) {
            logFile << fieldNames[i];
            if (i < fieldNames.size() - 1) {
                logFile << "|";
            }
        }
        logFile << std::endl;
    }

    // Parse each entry line
    while (getline(file, line)) {
        if (line.empty() || line == "---") continue;

        std::istringstream ss(line);
        Entry entry;
        std::string firstFieldValue;

        try {
            std::string fieldValue;
            size_t fieldIndex = 0;

            // Parse each field in the entry
            while (getline(ss, fieldValue, '|')) {
                if (fieldIndex >= schema.size()) {
                    throw MissingFieldException(line);
                }
                const auto& fieldFormat = schema[fieldIndex];
                if (fieldIndex == 0) {
                    firstFieldValue = fieldValue; // Store the first field for uniqueness check
                    if (firstFieldValue.empty()) throw MissingFieldException(line);
                }
                if (fieldValue.empty()) throw MissingFieldException(line);

                // Handle single-value fields
                if (fieldFormat.multiplicity == FieldType::Single) {
                    switch (fieldFormat.type) {
                        case DataType::String:
                            entry.fields.push_back(std::make_shared<FieldSingle<std::string>>(parseValue<std::string>(fieldValue)));
                            break;
                        case DataType::Integer:
                            entry.fields.push_back(std::make_shared<FieldSingle<int>>(parseValue<int>(fieldValue)));
                            break;
                        case DataType::Double:
                            entry.fields.push_back(std::make_shared<FieldSingle<double>>(parseValue<double>(fieldValue)));
                            break;
                        case DataType::Bool:
                            entry.fields.push_back(std::make_shared<FieldSingle<bool>>(parseValue<bool>(fieldValue)));
                            break;
                    }
                } 
                // Handle multi-value fields
                else {
                    std::istringstream fs(fieldValue);
                    std::string value;
                    std::vector<std::string> stringValues;
                    std::vector<int> intValues;
                    std::vector<double> doubleValues;
                    std::vector<bool> boolValues;

                    while (getline(fs, value, ':')) {
                        if (value.empty()) throw MissingFieldException(line);
                        switch (fieldFormat.type) {
                            case DataType::String: stringValues.push_back(value); break;
                            case DataType::Integer: intValues.push_back(parseValue<int>(value)); break;
                            case DataType::Double: doubleValues.push_back(parseValue<double>(value)); break;
                            case DataType::Bool: boolValues.push_back(parseValue<bool>(value)); break;
                        }
                    }

                    switch (fieldFormat.type) {
                        case DataType::String: entry.fields.push_back(std::make_shared<FieldMulti<std::string>>(stringValues)); break;
                        case DataType::Integer: entry.fields.push_back(std::make_shared<FieldMulti<int>>(intValues)); break;
                        case DataType::Double: entry.fields.push_back(std::make_shared<FieldMulti<double>>(doubleValues)); break;
                        case DataType::Bool: entry.fields.push_back(std::make_shared<FieldMulti<bool>>(boolValues)); break;
                    }
                }
                fieldIndex++;
            }

            // Validate the entry
            if (entry.fields.size() < schema.size()) {
                throw MissingFieldException(line);
            }

            // Check for duplicate entries
            if (!uniqueEntries.insert(firstFieldValue).second) {
                throw DuplicateEntryException(line);
            }

            entries.push_back(entry); // Add the entry to the list
            uniqueCount++;
        } catch (const MissingFieldException& e) {
            logException(e.what());
        } catch (const DuplicateEntryException& e) {
            logException(e.what());
        } catch (const std::exception& e) {
            logException("Exception: parsing error\n" + line);
        }
    }

    logFile << uniqueCount << " unique entries" << std::endl;
    file.close();
}

// Processes commands from a file (search, sort)
void CatalogManager::processCommands(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Commands file could not be opened.");
    }
    
    std::string line;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue; // Skip empty lines and comments
        }
        
        std::istringstream ss(line);
        std::string commandType;
        ss >> commandType;
        
        try {
            if (commandType == "search") {
                std::string value = getQuotedString(ss);
                
                std::string inKeyword;
                ss >> std::ws >> inKeyword;
                
                if (trim(inKeyword) != "in") {
                    throw WrongCommandException();
                }
                
                ss >> std::ws;
                std::string fieldName = getQuotedString(ss);
                
                if (value.empty() || fieldName.empty() || !fieldExists(fieldName)) {
                    throw WrongCommandException();
                }
                
                logFile << line << std::endl;
                search(fieldName, value); // Execute search command
                
            } else if (commandType == "sort") {
                std::string fieldName = getQuotedString(ss);
                
                if (fieldName.empty() || !fieldExists(fieldName)) {
                    throw WrongCommandException();
                }
                
                logFile << line << std::endl;
                sort(fieldName); // Execute sort command
                
            } else {
                throw WrongCommandException();
            }
        } catch (const WrongCommandException& e) {
            logException(e.what());
            logFile << line << std::endl;
        }
    }
    
    file.close();
}

// Searches for entries where the specified field contains the given value
void CatalogManager::search(const std::string& fieldName, const std::string& value) {
    bool found = false;
    int fieldIndex = getFieldIndex(fieldName);
    
    if (fieldIndex == -1) {
        logException("Exception: field not found\n" + fieldName);
        return;
    }
    
    // Iterate through entries and check for matches
    for (const auto& entry : entries) {
        if (static_cast<size_t>(fieldIndex) < entry.fields.size() && entry.fields[fieldIndex]) {
            std::string fieldValue = entry.fields[fieldIndex]->toString();
            if (fieldValue.find(value) != std::string::npos) {
                logFile << entry.getFormattedEntry(schema) << std::endl;
                found = true;
            }
        }
    }
    
    if (!found) {
        // No action taken if no matches are found
    }
}

// Sorts entries by the specified field and logs the sorted result
void CatalogManager::sort(const std::string& fieldName) {
    int fieldIndex = getFieldIndex(fieldName);
    
    if (fieldIndex == -1) {
        logException("Exception: field not found\n" + fieldName);
        return;
    }
    
    const auto& fieldFormat = schema[fieldIndex];
    
    // Comparator for sorting entries
    auto compareEntries = [fieldIndex, &fieldFormat](const Entry& a, const Entry& b) -> bool {
        if (static_cast<size_t>(fieldIndex) >= a.fields.size() || 
            static_cast<size_t>(fieldIndex) >= b.fields.size() || 
            !a.fields[fieldIndex] || !b.fields[fieldIndex]) {
            return false;
        }
        
        std::string aValue = a.fields[fieldIndex]->toString();
        std::string bValue = b.fields[fieldIndex]->toString();
        
        // For multi-value fields, compare the first value
        if (fieldFormat.multiplicity == FieldType::Multi) {
            size_t aDelim = aValue.find(':');
            size_t bDelim = bValue.find(':');
            
            if (aDelim != std::string::npos) {
                aValue = aValue.substr(0, aDelim);
            }
            
            if (bDelim != std::string::npos) {
                bValue = bValue.substr(0, bDelim);
            }
        }
        
        // Compare based on field type
        switch (fieldFormat.type) {
            case DataType::Integer:
                return (aValue.empty() ? 0 : std::stoi(aValue)) < (bValue.empty() ? 0 : std::stoi(bValue));
            case DataType::Double:
                return (aValue.empty() ? 0.0 : std::stod(aValue)) < (bValue.empty() ? 0.0 : std::stod(bValue));
            case DataType::Bool:
                return (parseValue<bool>(aValue)) < (parseValue<bool>(bValue));
            default: // String
                return aValue < bValue;
        }
    };
    
    // Sort the entries
    std::vector<Entry> sortedEntries = entries;
    std::sort(sortedEntries.begin(), sortedEntries.end(), compareEntries);
    
    // Log the sorted entries
    for (const auto& entry : sortedEntries) {
        logFile << entry.getFormattedEntry(schema) << std::endl;
    }
}