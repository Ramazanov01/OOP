 #include "WordString.h"
 #include <cstring>
 
 // Custom function to check if a character is a space (replacing isspace from cctype)
 bool WordString::isSpace(char c) const {
     return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
 }
 
 // Default constructor
 WordString::WordString() : words(nullptr), spaces(nullptr), wordCount(0) {}
 
 // Constructor from C-string
 WordString::WordString(const char* input) : words(nullptr), spaces(nullptr), wordCount(0) {
     if (input) {
         tokenize(input);
     }
 }
 
 // Constructor from std::string
 WordString::WordString(const std::string& input) : words(nullptr), spaces(nullptr), wordCount(0) {
     tokenize(input.c_str());
 }
 
 // Copy constructor
 WordString::WordString(const WordString& other) : words(nullptr), spaces(nullptr), wordCount(0) {
     copy(other);
 }
 
 // Destructor
 WordString::~WordString() {
     cleanup();
 }
 
 // Assignment operator
 WordString& WordString::operator=(const WordString& other) {
     if (this != &other) {
         cleanup();
         copy(other);
     }
     return *this;
 }

void WordString::tokenize(const char* input) {
    cleanup(); // Temiz sayfa açalım

    if (!input || input[0] == '\0') return;

    // Başlangıç kapasitesi
    int capacity = 10;
    wordCount = 0;
    words = new char*[capacity];
    spaces = new int[capacity];

    int i = 0;

    while (input[i] != '\0') {
        // Boşlukları atla
        while (isSpace(input[i])) i++;
        if (input[i] == '\0') break;

        // Kapasite yetmezse genişlet
        if (wordCount >= capacity) {
            // Kapasiteyi iki katla
            int newCapacity = capacity * 2;
            char** newWords = new char*[newCapacity];
            int* newSpaces = new int[newCapacity];

            // Eski verileri taşı
            for (int j = 0; j < wordCount; j++) {
                newWords[j] = words[j];
                newSpaces[j] = spaces[j];
            }

            delete[] words;
            delete[] spaces;

            words = newWords;
            spaces = newSpaces;
            capacity = newCapacity;
        }

        // Kelime başlangıcı
        int start = i;
        while (input[i] != '\0' && !isSpace(input[i])) i++;
        int end = i;

        int len = end - start;
        words[wordCount] = new char[len + 1];
        strncpy(words[wordCount], input + start, len);
        words[wordCount][len] = '\0';

        // Boşluk say
        int spaceCount = 0;
        while (isSpace(input[i])) {
            spaceCount++;
            i++;
        }
        spaces[wordCount] = spaceCount;

        wordCount++;
    }

    // Son kelimenin boşluğunu sıfırla
    if (wordCount > 0) {
        spaces[wordCount - 1] = 0;
    }
}
 
 // Helper function to free dynamically allocated memory
 void WordString::cleanup() {
     if (words) {
         for (int i = 0; i < wordCount; i++) {
             delete[] words[i];
         }
         delete[] words;
         words = nullptr;
     }
     
     if (spaces) {
         delete[] spaces;
         spaces = nullptr;
     }
     
     wordCount = 0;
 }
 
 // Helper function for deep copying
 void WordString::copy(const WordString& other) {
     if (other.wordCount > 0) {
         wordCount = other.wordCount;
         words = new char*[wordCount];
         spaces = new int[wordCount];
         
         for (int i = 0; i < wordCount; i++) {
             // Deep copy each word
             size_t len = strlen(other.words[i]);
             words[i] = new char[len + 1];
             strcpy(words[i], other.words[i]);
             
             // Copy spaces
             spaces[i] = other.spaces[i];
         }
     }
 }
 
 // Equality operator
 bool WordString::operator==(const WordString& other) const {
     if (wordCount != other.wordCount) {
         return false;
     }
     
     for (int i = 0; i < wordCount; i++) {
         // Compare words
         if (strcmp(words[i], other.words[i]) != 0) {
             return false;
         }
         
         // Compare spaces
         if (spaces[i] != other.spaces[i]) {
             return false;
         }
     }
     
     return true;
 }
 
 // Concatenation operator for WordString
 WordString WordString::operator+(const WordString& other) const {
     // Calculate the total size needed
     int totalLength = 0;
     
     // Add space for all words and spaces in this object
     for (int i = 0; i < wordCount; i++) {
         totalLength += strlen(words[i]);
         totalLength += spaces[i]; // Add spaces after each word
     }
     
     // Add space for all words and spaces in the other object
     // Add an extra space between the objects
     if (wordCount > 0 && other.wordCount > 0) {
         totalLength += 1; // Space between objects
     }
     
     for (int i = 0; i < other.wordCount; i++) {
         totalLength += strlen(other.words[i]);
         totalLength += other.spaces[i]; // Add spaces after each word
     }
     
     // Create a temporary buffer for the concatenated string
     char* buffer = new char[totalLength + 1]; // +1 for null terminator
     buffer[0] = '\0'; // Initialize as empty string
     
     // Copy all words and spaces from this object
     for (int i = 0; i < wordCount; i++) {
         strcat(buffer, words[i]);
         
         // Add spaces after the word
         for (int j = 0; j < spaces[i]; j++) {
             strcat(buffer, " ");
         }
     }
     
     // Add a space between objects if needed
     if (wordCount > 0 && other.wordCount > 0) {
         strcat(buffer, " ");
     }
     
     // Copy all words and spaces from the other object
     for (int i = 0; i < other.wordCount; i++) {
         strcat(buffer, other.words[i]);
         
         // Add spaces after the word
         for (int j = 0; j < other.spaces[i]; j++) {
             strcat(buffer, " ");
         }
     }
     
     // Create a new WordString from the buffer
     WordString result(buffer);
     delete[] buffer;
     
     return result;
 }
 
 // Concatenation operator for std::string
 WordString WordString::operator+(const std::string& other) const {
     // Convert the std::string to a C-string
     const char* otherCStr = other.c_str();
     
     // Use the C-string concatenation function
     return *this + otherCStr;
 }
 
 // Concatenation operator for C-string
 WordString WordString::operator+(const char* other) const {
     // Calculate the total size needed
     int totalLength = 0;
     
     // Add space for all words and spaces in this object
     for (int i = 0; i < wordCount; i++) {
         totalLength += strlen(words[i]);
         totalLength += spaces[i]; // Add spaces after each word
     }
     
     // Add a space between objects if needed
     if (wordCount > 0) {
         totalLength += 1; // Space between objects
     }
     
     // Add space for the other C-string
     totalLength += strlen(other);
     
     // Create a temporary buffer for the concatenated string
     char* buffer = new char[totalLength + 1]; // +1 for null terminator
     buffer[0] = '\0'; // Initialize as empty string
     
     // Copy all words and spaces from this object
     for (int i = 0; i < wordCount; i++) {
         strcat(buffer, words[i]);
         
         // Add spaces after the word
         for (int j = 0; j < spaces[i]; j++) {
             strcat(buffer, " ");
         }
     }
     
     // Add a space between objects if needed
     if (wordCount > 0) {
         strcat(buffer, " ");
     }
     
     // Copy the other C-string
     strcat(buffer, other);
     
     // Create a new WordString from the buffer
     WordString result(buffer);
     delete[] buffer;
     
     return result;
 }
 
 // Output stream operator
 std::ostream& operator<<(std::ostream& os, const WordString& ws) {
     for (int i = 0; i < ws.wordCount; i++) {
         os << ws.words[i];
         
         // Add spaces after the word if not the last word
         for (int j = 0; j < ws.spaces[i]; j++) {
             os << " ";
         }
     }
     
     return os;
 }
 
 // Input stream operator
 std::istream& operator>>(std::istream& is, WordString& ws) {
     // Define a buffer size
     const int BUFFER_SIZE = 1024;
     char buffer[BUFFER_SIZE];
     
     // Read a string from the input stream
     is >> buffer;
     
     // Create a new WordString from the input
     //ws.cleanup();
     ws.tokenize(buffer);
     
     return is;
 }
 
 // Get word at specified index
 std::string WordString::get(int index) const {
     if (index < 0 || index >= wordCount) {
         return ""; // Return empty string for invalid index
     }
     
     return std::string(words[index]);
 }

void WordString::replace(int index, const std::string& text) {
    if (index < 0 || index >= wordCount) return;

    // Tokenize edilen yeni kelimeleri al
    WordString newWords(text);
    if (newWords.wordCount == 0) return;

    // Yeni toplam kelime sayısı
    int newWordCount = wordCount - 1 + newWords.wordCount;

    char** newWordArray = new char*[newWordCount];
    int* newSpaceArray = new int[newWordCount];

    int pos = 0;

    // Önceki kelimeleri kopyala
    for (int i = 0; i < index; i++, pos++) {
        newWordArray[pos] = new char[strlen(words[i]) + 1];
        strcpy(newWordArray[pos], words[i]);
        newSpaceArray[pos] = spaces[i];
    }

    // Yeni kelimeleri ekle
    for (int i = 0; i < newWords.wordCount; i++, pos++) {
        newWordArray[pos] = new char[strlen(newWords.words[i]) + 1];
        strcpy(newWordArray[pos], newWords.words[i]);
        // space ayarı: sondaysa eski space, ortadaysa 1
        if (i == newWords.wordCount - 1) {
            newSpaceArray[pos] = spaces[index]; // orijinal kelimenin space'i
        } else {
            newSpaceArray[pos] = newWords.spaces[i];
        }
    }

    // Sonraki kelimeleri kopyala
    for (int i = index + 1; i < wordCount; i++, pos++) {
        newWordArray[pos] = new char[strlen(words[i]) + 1];
        strcpy(newWordArray[pos], words[i]);
        newSpaceArray[pos] = spaces[i];
    }

    // Eski bellekleri temizle
    cleanup();
    words = newWordArray;
    spaces = newSpaceArray;
    wordCount = newWordCount;
}
 
 // Insert text after word at index
 void WordString::insertAfter(int index, const std::string& text) {
     if (index < 0 || index >= wordCount) {
         return; // Invalid index
     }
     
     // Tokenize the text to insert
     WordString textToInsert(text);
     
     if (textToInsert.wordCount == 0) {
         return; // Nothing to insert
     }
     
     // Create new arrays with increased size
     int newWordCount = wordCount + textToInsert.wordCount;
     char** newWords = new char*[newWordCount];
     int* newSpaces = new int[newWordCount];
     
     // Copy words before the insertion point
     for (int i = 0; i <= index; i++) {
         newWords[i] = new char[strlen(words[i]) + 1];
         strcpy(newWords[i], words[i]);
         newSpaces[i] = i == index ? 1 : spaces[i]; // Add one space after the word at index
     }
     
     // Copy the words to insert
     for (int i = 0; i < textToInsert.wordCount; i++) {
         int newIndex = index + 1 + i;
         newWords[newIndex] = new char[strlen(textToInsert.words[i]) + 1];
         strcpy(newWords[newIndex], textToInsert.words[i]);
         
         // Add one space after the last inserted word if it's not the last word overall
         newSpaces[newIndex] = (i == textToInsert.wordCount - 1 && index + 1 + i < newWordCount - 1) ? 1 : 
                              (i < textToInsert.wordCount - 1) ? textToInsert.spaces[i] : 0;
     }
     
     // Copy words after the insertion point
     for (int i = index + 1; i < wordCount; i++) {
         int newIndex = i + textToInsert.wordCount;
         newWords[newIndex] = new char[strlen(words[i]) + 1];
         strcpy(newWords[newIndex], words[i]);
         newSpaces[newIndex] = spaces[i];
     }
     
     // Update the object
     cleanup();
     words = newWords;
     spaces = newSpaces;
     wordCount = newWordCount;
 }
 
 // Insert text before word at index
 void WordString::insertBefore(int index, const std::string& text) {
     if (index < 0 || index >= wordCount) {
         return; // Invalid index
     }
     
     if (index == 0) {
         // Special case: insert at the beginning
         WordString textToInsert(text);
         if (textToInsert.wordCount == 0) {
             return; // Nothing to insert
         }
         
         // Create new arrays with increased size
         int newWordCount = wordCount + textToInsert.wordCount;
         char** newWords = new char*[newWordCount];
         int* newSpaces = new int[newWordCount];
         
         // Copy the words to insert
         for (int i = 0; i < textToInsert.wordCount; i++) {
             newWords[i] = new char[strlen(textToInsert.words[i]) + 1];
             strcpy(newWords[i], textToInsert.words[i]);
             newSpaces[i] = i < textToInsert.wordCount - 1 ? textToInsert.spaces[i] : 1; // Add one space after the last inserted word
         }
         
         // Copy existing words
         for (int i = 0; i < wordCount; i++) {
             int newIndex = i + textToInsert.wordCount;
             newWords[newIndex] = new char[strlen(words[i]) + 1];
             strcpy(newWords[newIndex], words[i]);
             newSpaces[newIndex] = spaces[i];
         }
         
         // Update the object
         cleanup();
         words = newWords;
         spaces = newSpaces;
         wordCount = newWordCount;
     } else {
         // Insert before a word that's not the first word
         // Equivalent to inserting after the previous word
         insertAfter(index - 1, text);
     }
 }

void WordString::remove(int index) {
    // Validate index
    if (index < 0 || index >= wordCount) {
        return;
    }

    // Special case for only one word
    if (wordCount == 1) {
        cleanup();
        return;
    }

    // Store the old wordCount before cleanup
    int oldWordCount = wordCount;
    
    // Create new arrays
    char** newWords = new char*[oldWordCount - 1];
    int* newSpaces = new int[oldWordCount - 1];

    // Copy words and spaces before the index
    for (int i = 0; i < index; i++) {
        newWords[i] = new char[strlen(words[i]) + 1];
        strcpy(newWords[i], words[i]);
        newSpaces[i] = spaces[i];
    }

    // Copy words and spaces after the index
    for (int i = index + 1; i < oldWordCount; i++) {
        int newIndex = i - 1;
        newWords[newIndex] = new char[strlen(words[i]) + 1];
        strcpy(newWords[newIndex], words[i]);
        newSpaces[newIndex] = spaces[i];
    }

    // Handle special space cases
    if (index > 0 && index < oldWordCount - 1) {
        // When removing a middle word, adjust spaces
        newSpaces[index-1] = spaces[index];
    }

    // Free old memory without setting wordCount to 0
    if (words) {
        for (int i = 0; i < oldWordCount; i++) {
            delete[] words[i];
        }
        delete[] words;
    }
    
    if (spaces) {
        delete[] spaces;
    }
    
    // Set new data
    words = newWords;
    spaces = newSpaces;
    wordCount = oldWordCount - 1;
}
 
 // Remove excessive spaces
 void WordString::strip() {
     if (wordCount == 0) {
         return;
     }
     
     // Set all spaces to 1 (or 0 for the last word)
     for (int i = 0; i < wordCount - 1; i++) {
         spaces[i] = 1;
     }
     spaces[wordCount - 1] = 0;
 }
 
 // Return number of words
 int WordString::numberOfWords() const {
     return wordCount;
 }
 
 // Convert to std::string
 std::string WordString::toString() const {
     std::string result;
     
     // Calculate the total size needed
     int totalLength = 0;
     for (int i = 0; i < wordCount; i++) {
         totalLength += strlen(words[i]);
         totalLength += spaces[i]; // Add spaces after each word
     }
     
     // Reserve space in the result string (optimization)
     result.reserve(totalLength);
     
     // Build the string
     for (int i = 0; i < wordCount; i++) {
         result += words[i];
         
         // Add spaces after the word
         for (int j = 0; j < spaces[i]; j++) {
             result += " ";
         }
     }
     
     return result;
 }
 
 // Debug function
 void WordString::printDetails() const {
     std::cout << "WordCount: " << wordCount << std::endl;
     for (int i = 0; i < wordCount; i++) {
         std::cout << "Word " << i << ": '" << words[i] << "' Spaces after: " << spaces[i] << std::endl;
     }
 }