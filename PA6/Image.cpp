#include "Image.h"
#include <iostream>

// Constructor: initialize MediaObject part with name/info and store the image dimension
Image::Image(const std::string &name, const std::string &dim, const std::string &info)
    : MediaObject(name, info), dimension(dim) {}

// Override MediaObject::info_display to print image-specific details
void Image::info_display() const {
    std::cout << "Image: " << name
              << ", Dimension: " << dimension
              << ", Info: " << info << std::endl;
}

// Implement Visual::display to simulate showing the image
void Image::display() const {
    std::cout << "Displaying image: " << name << std::endl;
}

// Implement Non_playable::view to simulate viewing the image
void Image::view() const {
    std::cout << "Viewing image: " << name << std::endl;
}

// Getter for the dimension field
std::string Image::getDimension() const {
    return dimension;
}

