#include <iostream>
#include "Text.h"

// Initialize BaseMedia with name and description
Text::Text(const std::string& name, const std::string& content)
    : BaseMedia(name, content) {}

// Default destructor
Text::~Text() {}

// Print format: "Text: <name>, Description: <content>"
void Text::info() const {
    std::cout << "Text: " << name
              << ", Description: " << infoText
              << std::endl;
}
