#ifndef BASEMEDIA_H
#define BASEMEDIA_H

#include <string>

// BaseMedia is an abstract class for all media items.
// It stores a name and an info text (e.g., duration or description).
class BaseMedia {
protected:
    std::string name;      // The media’s name (e.g., “audioname1”)
    std::string infoText;  // Additional info (e.g., “3:00, info1”)

public:
    // Constructor: sets name and infoText
    BaseMedia(const std::string& name, const std::string& info);

    // Virtual destructor (must be virtual because we delete via BaseMedia*)
    virtual ~BaseMedia();

    // Pure virtual method: each subclass must implement how to print itself
    virtual void info() const = 0;

    // Return the stored name
    std::string getName() const;
};

#endif // BASEMEDIA_H
