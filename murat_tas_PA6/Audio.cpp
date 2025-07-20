#include <iostream>
#include "Audio.h"

// Store infoText as "<duration>, <description>"
Audio::Audio(const std::string& name, const std::string& duration, const std::string& description)
    : BaseMedia(name, duration + ", " + description) {}

// Default destructor
Audio::~Audio() {}

// Print “Audio: <name>, Duration: <duration>, Description: <description>”
void Audio::info() const {
    // Split infoText at first comma
    std::string::size_type commaPos = infoText.find(", ");
    std::string dur = infoText.substr(0, commaPos);        // e.g., "3:00"
    std::string desc = infoText.substr(commaPos + 2);      // e.g., "info1"
    std::cout << "Audio: " << name
              << ", Duration: " << dur
              << ", Description: " << desc
              << std::endl;
}
