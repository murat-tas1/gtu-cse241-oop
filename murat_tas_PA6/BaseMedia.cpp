#include "BaseMedia.h"

// Initialize name and infoText
BaseMedia::BaseMedia(const std::string& name, const std::string& info)
    : name(name), infoText(info) {}

// Default destructor
BaseMedia::~BaseMedia() {}

// Return the media’s name
std::string BaseMedia::getName() const {
    return name;
}
