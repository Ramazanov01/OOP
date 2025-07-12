#include "Audio.h"
#include <iostream>

// Constructor: initialize MediaObject part with name/info and Playable part with duration
Audio::Audio(const std::string &name, const std::string &dur, const std::string &info)
    : MediaObject(name, info), Playable(dur) {}

// Display audio-specific details (overrides MediaObject::info_display)
void Audio::info_display() const {
    std::cout << "Audio: " << name
              << ", Duration: " << duration
              << ", Info: " << info << std::endl;
}

// Simulate processing of audio (implements NonVisual::process)
void Audio::process() const {
    std::cout << "Processing audio: " << name << std::endl;
}

// Simulate playing the audio (implements Playable::play)
void Audio::play() const {
    std::cout << "Playing audio: " << name
              << " (Duration: " << duration << ")" << std::endl;
}

