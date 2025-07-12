#include "Playable.h"

// Constructor: initialize the 'duration' field using an initializer list
Playable::Playable(const std::string &dur) : duration(dur) {}

// Default destructor (virtual) to allow proper cleanup in derived classes
Playable::~Playable() = default;

// Getter for the 'duration' field
std::string Playable::getDuration() const {
    return duration;
}

