#include "MediaObject.h"

// Constructor: initialize 'name' and 'info' fields using initializer list
MediaObject::MediaObject(const std::string &n, const std::string &i)
    : name(n), info(i) {}

// Default destructor (virtual)
MediaObject::~MediaObject() = default;

// Getter for the 'name' field
std::string MediaObject::getName() const {
    return name;
}

// Getter for the 'info' field
std::string MediaObject::getInfo() const {
    return info;
}
