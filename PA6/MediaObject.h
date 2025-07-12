#ifndef MEDIAOBJECT_H
#define MEDIAOBJECT_H

#include <string>

// The abstract base class for all media objects.
// Holds common 'name' and 'info' fields and declares a pure virtual method for displaying info.
class MediaObject {
protected:
    std::string name;  // The name of the media object
    std::string info;  // Additional information or description

public:
    // Constructor: initialize 'name' and 'info'
    MediaObject(const std::string &n, const std::string &i);

    // Virtual destructor to allow proper cleanup in derived classes
    virtual ~MediaObject();

    // Pure virtual method: each subclass must implement its own info display logic
    virtual void info_display() const = 0;

    // Getter for the name field
    std::string getName() const;

    // Getter for the info field
    std::string getInfo() const;
};

#endif // MEDIAOBJECT_H
