#include "Player.h"
#include "Audio.h"
#include "Video.h"
#include <iostream>
#include <stdexcept>

// Constructor: initialize currentIndex to -1 (no item) and dataset pointer to nullptr
Player::Player()
    : currentIndex(-1), dataset(nullptr) {}

// Store the Dataset pointer so update() can fetch the current list of playables
void Player::setDataset(Dataset* ds) {
    dataset = ds;
}

// Called whenever the Dataset changes: grab the updated list of Playable objects
void Player::update() {
    playlist = dataset->getPlayableObjects();

    // If the previous currentIndex is out of range, reset appropriately
    if (currentIndex >= static_cast<int>(playlist.size())) {
        currentIndex = playlist.empty() ? -1 : 0;
    }
    // If there was no current item but the playlist is now non-empty, start at 0
    if (currentIndex == -1 && !playlist.empty()) {
        currentIndex = 0;
    }
}

// Print the playlist, marking the currently playing item
void Player::show_list() const {
    std::cout << "\n=== Player Playlist ===" << std::endl;
    if (playlist.empty()) {
        std::cout << "Playlist is empty." << std::endl;
        return;
    }

    for (size_t i = 0; i < playlist.size(); ++i) {
        std::cout << i + 1 << ". ";
        MediaObject* obj = dynamic_cast<MediaObject*>(playlist[i]);
        if (obj) {
            std::cout << obj->getName();
            if (static_cast<int>(i) == currentIndex) {
                std::cout << " [CURRENTLY PLAYING]";
            }
            std::cout << std::endl;
        }
    }
}

// Return the currently playing item or throw if none exists
Playable* Player::currently_playing() {
    if (playlist.empty() || currentIndex == -1) {
        throw std::runtime_error("No item currently playing - playlist is empty!");
    }
    return playlist[currentIndex];
}

// Move to the next item of the given type ("audio", "video", or any if type is empty/unknown)
void Player::next(const std::string &type) {
    if (playlist.empty()) {
        std::cout << "Cannot move to next - playlist is empty!" << std::endl;
        return;
    }

    int startIndex = currentIndex;
    do {
        currentIndex = (currentIndex + 1) % playlist.size();
        if (matchesType(playlist[currentIndex], type)) {
            std::cout << "Moved to next " << type << ": ";
            MediaObject* obj = dynamic_cast<MediaObject*>(playlist[currentIndex]);
            if (obj) std::cout << obj->getName() << std::endl;
            return;
        }
    } while (currentIndex != startIndex);

    std::cout << "No " << type << " found in playlist!" << std::endl;
}

// Move to the previous item of the given type ("audio", "video", or any if type is empty/unknown)
void Player::previous(const std::string &type) {
    if (playlist.empty()) {
        std::cout << "Cannot move to previous - playlist is empty!" << std::endl;
        return;
    }

    int startIndex = currentIndex;
    do {
        currentIndex = (currentIndex - 1 + playlist.size()) % playlist.size();
        if (matchesType(playlist[currentIndex], type)) {
            std::cout << "Moved to previous " << type << ": ";
            MediaObject* obj = dynamic_cast<MediaObject*>(playlist[currentIndex]);
            if (obj) std::cout << obj->getName() << std::endl;
            return;
        }
    } while (currentIndex != startIndex);

    std::cout << "No " << type << " found in playlist!" << std::endl;
}

// Helper: check if the Playable object matches the requested type
bool Player::matchesType(Playable* obj, const std::string &type) const {
    if (type == "audio") {
        return dynamic_cast<Audio*>(obj) != nullptr;
    } else if (type == "video") {
        return dynamic_cast<Video*>(obj) != nullptr;
    }
    // If type is not specified or unknown, accept any Playable
    return true;
}
