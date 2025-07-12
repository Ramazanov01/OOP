#include "Viewer.h"
#include "Image.h"
#include "Text.h"
#include <iostream>
#include <stdexcept>

// Constructor: initialize currentIndex to -1 (no item) and dataset pointer to nullptr
Viewer::Viewer()
    : currentIndex(-1), dataset(nullptr) {}

// Store the Dataset pointer so update() can fetch the current list of non-playables
void Viewer::setDataset(Dataset* ds) {
    dataset = ds;
}

// Called whenever the Dataset changes: grab the updated list of Non_playable objects
void Viewer::update() {
    viewlist = dataset->getNonPlayableObjects();

    // If the previous currentIndex is out of range, reset appropriately
    if (currentIndex >= static_cast<int>(viewlist.size())) {
        currentIndex = viewlist.empty() ? -1 : 0;
    }
    // If there was no current item but the viewlist is now non-empty, start at 0
    if (currentIndex == -1 && !viewlist.empty()) {
        currentIndex = 0;
    }
}

// Print the viewlist, marking the currently viewing item
void Viewer::show_list() const {
    std::cout << "\n=== Viewer List ===" << std::endl;
    if (viewlist.empty()) {
        std::cout << "View list is empty." << std::endl;
        return;
    }

    for (size_t i = 0; i < viewlist.size(); ++i) {
        std::cout << i + 1 << ". ";
        MediaObject* obj = dynamic_cast<MediaObject*>(viewlist[i]);
        if (obj) {
            std::cout << obj->getName();
            if (static_cast<int>(i) == currentIndex) {
                std::cout << " [CURRENTLY VIEWING]";
            }
            std::cout << std::endl;
        }
    }
}

// Return the currently viewing item or throw if none exists
Non_playable* Viewer::currently_viewing() {
    if (viewlist.empty() || currentIndex == -1) {
        throw std::runtime_error("No item currently viewing - view list is empty!");
    }
    return viewlist[currentIndex];
}

// Move to the next item of the given type ("text", "image", or any if type is empty/unknown)
void Viewer::next(const std::string &type) {
    if (viewlist.empty()) {
        std::cout << "Cannot move to next - view list is empty!" << std::endl;
        return;
    }

    int startIndex = currentIndex;
    do {
        currentIndex = (currentIndex + 1) % viewlist.size();
        if (matchesType(viewlist[currentIndex], type)) {
            std::cout << "Moved to next " << type << ": ";
            MediaObject* obj = dynamic_cast<MediaObject*>(viewlist[currentIndex]);
            if (obj) std::cout << obj->getName() << std::endl;
            return;
        }
    } while (currentIndex != startIndex);

    std::cout << "No " << type << " found in view list!" << std::endl;
}

// Move to the previous item of the given type ("text", "image", or any if type is empty/unknown)
void Viewer::previous(const std::string &type) {
    if (viewlist.empty()) {
        std::cout << "Cannot move to previous - view list is empty!" << std::endl;
        return;
    }

    int startIndex = currentIndex;
    do {
        currentIndex = (currentIndex - 1 + viewlist.size()) % viewlist.size();
        if (matchesType(viewlist[currentIndex], type)) {
            std::cout << "Moved to previous " << type << ": ";
            MediaObject* obj = dynamic_cast<MediaObject*>(viewlist[currentIndex]);
            if (obj) std::cout << obj->getName() << std::endl;
            return;
        }
    } while (currentIndex != startIndex);

    std::cout << "No " << type << " found in view list!" << std::endl;
}

// Helper: check if the Non_playable object matches the requested type
bool Viewer::matchesType(Non_playable* obj, const std::string &type) const {
    if (type == "text") {
        return dynamic_cast<Text*>(obj) != nullptr;
    } else if (type == "image") {
        return dynamic_cast<Image*>(obj) != nullptr;
    }
    // If type is not specified or unknown, accept any Non_playable
    return true;
}
