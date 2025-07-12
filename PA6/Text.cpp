#include "Text.h"
#include <iostream>

// Constructor: initialize MediaObject with name and info
Text::Text(const std::string &name, const std::string &info)
    : MediaObject(name, info) {}

// Override MediaObject::info_display to print text-specific details
void Text::info_display() const {
    std::cout << "Text: " << name
              << ", Info: " << info << std::endl;
}

// Implement Non_Visual::process to simulate processing the text
void Text::process() const {
    std::cout << "Processing text: " << name << std::endl;
}

// Implement Non_playable::view to simulate viewing the text
void Text::view() const {
    std::cout << "Viewing text: " << name << std::endl;
}
