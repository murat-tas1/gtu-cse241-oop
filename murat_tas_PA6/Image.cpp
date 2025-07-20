// Image.cpp
#include <iostream>
#include "Image.h"

// Notice the types: (const std::string& , const std::string& , const std::string&)
// They must match the declaration in Image.h precisely.

Image::Image(const std::string& name, 
             const std::string& dimensions, 
             const std::string& description)
    : BaseMedia(name, dimensions + ", " + description)
{
    // We are storing "dimensions, description" in BaseMedia::infoText
}

Image::~Image() {}

// Print “Image: <name>, Dimensions: <dim>, Description: <desc>”
void Image::info() const {
    // Split the stored infoText at the first comma:
    auto commaPos = infoText.find(", ");
    std::string dims = infoText.substr(0, commaPos);
    std::string desc = infoText.substr(commaPos + 2);
    std::cout << "Image: " << name
              << ", Dimensions: " << dims
              << ", Description: " << desc
              << std::endl;
}
