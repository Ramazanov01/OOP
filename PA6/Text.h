#ifndef TEXT_H
#define TEXT_H

#include "MediaObject.h"
#include "NonVisual.h"
#include "NonPlayable.h"
#include <string>

// The Text class represents a text-based media object.
// It inherits MediaObject for basic name/info storage,
// implements Non_Visual to allow processing,
// and implements Non_playable to allow viewing.
class Text : public MediaObject, public Non_Visual, public Non_playable {
public:
    // Constructor: initialize the base MediaObject with name and info
    Text(const std::string &name, const std::string &info);

    // Override MediaObject::info_display to print text-specific details
    void info_display() const override;

    // Override Non_Visual::process to simulate processing text
    void process() const override;

    // Override Non_playable::view to simulate viewing text
    void view() const override;
};

#endif // TEXT_H
