#include "CatalogManager.h"

// Constructor to initialize a Field object
Field::Field(const std::string &n, const std::string &t, const std::string &ia) : name(n), type(t), isArray(ia == "multi") {}

// Function to format a record according to the schema
std::string Record::getFormattedRecord(const std::vector<Field> &schema) const
{
	std::stringstream recordStream;
	for (const auto &field : schema)
	{
		if (fields.find(field.name) != fields.end())
		{
			if (field.isArray)
			{
				std::string joinedValues = join(fields.at(field.name), ":");
				recordStream << joinedValues << "|";
			}
			else
			{
				recordStream << fields.at(field.name).front() << "|";
			}
		}
		else
		{
			recordStream << "|"; // Empty value for missing field
		}
	}
	std::string result = recordStream.str();
	result.pop_back(); // Remove the last '|'
	return result;
}

// Function to join a vector of strings with a delimiter
std::string Record::join(const std::vector<std::string> &vec, const std::string &delim)
{
	std::ostringstream imploded;
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(imploded, delim.c_str()));
	std::string result = imploded.str();
	if (!result.empty())
	{
		result = result.substr(0, result.size() - delim.size()); // Remove the last delimiter
	}
	return result;
}

// Constructor to open the log file
CatalogManager::CatalogManager()
{
	logFile.open("output.txt");
	if (!logFile.is_open())
	{
		throw std::runtime_error("Log file could not be opened.");
	}
}

// Destructor to close the log file
CatalogManager::~CatalogManager()
{
	if (logFile.is_open())
	{
		logFile.close();
	}
}

// Function to log exceptions to the log file
void CatalogManager::logException(const std::string &message)
{
	logFile << message << std::endl;
}

// Helper function to trim spaces and quotes from a string
std::string CatalogManager::trim(const std::string &str)
{
	if (str.empty())
		return str;
	size_t first = str.find_first_not_of(" \"");
	if (first == std::string::npos)
		return "";
	size_t last = str.find_last_not_of(" \"");
	return str.substr(first, (last - first + 1));
}

// Function to check if a field exists in the schema
bool CatalogManager::fieldExists(const std::string &fieldName)
{
	return std::any_of(schema.begin(), schema.end(), [&fieldName](const Field &field)
					   { return field.name == fieldName; });
}

// Function to parse the catalog from the given file
void CatalogManager::parseCatalog(const std::string &filename)
{
	std::ifstream file(filename);
	std::string line;
	int uniqueCount = 0;

	// Read and parse the schema line
	if (getline(file, line))
	{
		std::istringstream ss(line);
		std::string fieldDef;
		std::vector<std::string> fieldNames; // To store field names
		while (getline(ss, fieldDef, '|'))
		{
			std::istringstream fds(fieldDef);
			std::string name, type, isArray;
			getline(fds, name, ':');
			getline(fds, type, ':');
			getline(fds, isArray, ':');
			schema.emplace_back(name, type, isArray);
			fieldNames.push_back(name); // Store field name
		}
		// Write field names to log file
		for (size_t i = 0; i < fieldNames.size(); ++i)
		{
			logFile << fieldNames[i];
			if (i < fieldNames.size() - 1)
			{
				logFile << "|";
			}
		}
		logFile << std::endl;
	}

	// Read and parse the records
	while (getline(file, line))
	{
		std::istringstream ss(line);
		std::string token;
		Record record;
		size_t index = 0;
		bool isValid = true;
		bool hasMissingField = false;

		// Parse each field in the record
		while (getline(ss, token, '|') && index < schema.size())
		{
			std::istringstream fs(token);
			std::string value;
			while (getline(fs, value, schema[index].isArray ? ':' : '\0'))
			{
				record.fields[schema[index].name].push_back(value);
			}
			++index;
		}

		// Check for missing fields
		if (index < schema.size())
		{
			logException("Exception: missing field\n" + line);
			hasMissingField = true;
			isValid = false;
		}

		std::string firstFieldValue = record.fields.begin()->second.front();

		// Check for duplicate entries only if there are no missing fields
		if (!hasMissingField && !uniqueEntries.insert(firstFieldValue).second)
		{
			logException("Exception: duplicate entry\n" + line);
			isValid = false;
		}

		// Add valid record to records
		if (isValid)
		{
			records.push_back(record);
			uniqueCount++;
		}
	}
	logFile << uniqueCount << " unique entries" << std::endl;
	file.close();
}

// Function to process commands from the given file
void CatalogManager::processCommands(const std::string &filename)
{
	std::ifstream file(filename);
	std::string line;
	int lineNumber = 0;

	// Read and process each command
	while (getline(file, line))
	{
		lineNumber++;

		std::istringstream ss(line);
		std::string commandType;
		ss >> commandType;
		if (commandType == "search")
		{
			std::string value, dummy, fieldName;
			value = getQuotedString(ss); // Get quoted string value
			ss >> dummy;
			fieldName = getQuotedString(ss); // Get quoted field name
			fieldName = trim(fieldName);
			value = trim(value);
			if (!fieldExists(fieldName))
			{
				logException("Exception: command is wrong");
				logFile << line << std::endl;
			}
			else
			{
				logFile << line << std::endl;
				search(fieldName, value);
			}
		}
		else if (commandType == "sort")
		{
			std::string fieldName;
			fieldName = getQuotedString(ss); // Get quoted field name
			fieldName = trim(fieldName);
			if (!fieldExists(fieldName))
			{
				logException("Exception: command is wrong");
				logFile << line << std::endl;
			}
			else
			{
				logFile << line << std::endl;
				sort(fieldName);
			}
		}
		else
		{
			logException("Exception: command is wrong");
			logFile << line << std::endl;
		}
	}
	file.close();
}

// Function to search for a value in a given field
void CatalogManager::search(const std::string &fieldName, const std::string &value)
{
	bool found = false;
	for (const auto &record : records)
	{
		try
		{
			const auto &fieldValues = record.fields.at(fieldName);
			for (const auto &fieldValue : fieldValues)
			{
				if (fieldValue.find(value) != std::string::npos)
				{
					logFile << record.getFormattedRecord(schema) << std::endl;
					found = true;
				}
			}
		}
		catch (const std::out_of_range &e)
		{
			//logException("Exception: field not found\n" + fieldName);
		}
	}
	if (!found)
	{
		logFile << "Not found" << std::endl;
	}
}

// Function to sort records by a given field
void CatalogManager::sort(const std::string &fieldName)
{
	// Find the index of the field in the schema
	int fieldIndex = -1;
	for (size_t i = 0; i < schema.size(); ++i)
	{
		if (schema[i].name == fieldName)
		{
			fieldIndex = i;
			break;
		}
	}

	if (fieldIndex == -1)
	{
		logException("Exception: field not found in schema\n" + fieldName);
		return;
	}

	// Collect valid records for sorting
	std::vector<const Record *> validRecords;
	for (const auto &record : records)
	{
		if (record.fields.find(fieldName) != record.fields.end())
		{
			validRecords.push_back(&record);
		}
	}

	// Sort the records based on the field type
	if (schema[fieldIndex].type == "integer")
	{
		std::sort(validRecords.begin(), validRecords.end(), [&fieldName](const Record *a, const Record *b)
				  { return std::stoi(a->fields.at(fieldName).front()) < std::stoi(b->fields.at(fieldName).front()); });
	}
	else
	{
		std::sort(validRecords.begin(), validRecords.end(), [&fieldName](const Record *a, const Record *b)
				  { return a->fields.at(fieldName).front() < b->fields.at(fieldName).front(); });
	}

	// Write sorted records to log file
	for (const auto &record : validRecords)
	{
		logFile << record->getFormattedRecord(schema) << std::endl;
	}
}

// Helper function to get quoted string from input stream
std::string CatalogManager::getQuotedString(std::istringstream &ss)
{
	char ch;
	std::string result;
	ss >> ch; // Read the opening quote
	while (ss.get(ch))
	{
		if (ch == '"')
		{
			break; // Found the closing quote
		}
		result += ch;
	}
	return result;
}
