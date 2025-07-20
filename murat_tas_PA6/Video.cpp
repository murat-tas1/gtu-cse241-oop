#include <iostream>
#include "Video.h"

// Store infoText as "<duration>, <description>"
Video::Video(const std::string& name, const std::string& duration, const std::string& description)
    : BaseMedia(name, duration + ", " + description) {}

// Default destructor
Video::~Video() {}

// Print “Video: <name>, Duration: <duration>, Description: <description>”
void Video::info() const {
    // Split infoText at first comma
    std::string::size_type commaPos = infoText.find(", ");
    std::string dur = infoText.substr(0, commaPos);        // e.g., "5:00"
    std::string desc = infoText.substr(commaPos + 2);      // e.g., "info1"
    std::cout << "Video: " << name
              << ", Duration: " << dur
              << ", Description: " << desc
              << std::endl;
}
