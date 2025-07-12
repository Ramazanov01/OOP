#ifndef AUDIO_H
#define AUDIO_H

#include "MediaObject.h"
#include "NonVisual.h"
#include "Playable.h"
#include <string>

// The Audio class represents an audio media object.
// Inherits MediaObject for name/info storage,
// implements Non_Visual to allow processing,
// and implements Playable to allow playing.
class Audio : public MediaObject, public Non_Visual, public Playable {
public:
    // Constructor: initialize MediaObject with name/info and Playable with duration
    Audio(const std::string &name, const std::string &dur, const std::string &info);

    // Override MediaObject::info_display to print audio-specific details
    void info_display() const override;

    // Override Non_Visual::process to simulate processing audio
    void process() const override;

    // Override Playable::play to simulate playing the audio
    void play() const override;
};

#endif // AUDIO_H
