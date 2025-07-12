#include "Video.h"
#include <iostream>

// Constructor: initialize MediaObject with name/info and Playable with duration
Video::Video(const std::string &name, const std::string &dur, const std::string &info)
    : MediaObject(name, info), Playable(dur) {}

// Override MediaObject::info_display to print video-specific details
void Video::info_display() const {
    std::cout << "Video: " << name
              << ", Duration: " << duration
              << ", Info: " << info << std::endl;
}

// Implement Visual::display to simulate showing the video
void Video::display() const {
    std::cout << "Displaying video: " << name << std::endl;
}

// Implement Playable::play to simulate playing the video
void Video::play() const {
    std::cout << "Playing video: " << name
              << " (Duration: " << duration << ")" << std::endl;
}
