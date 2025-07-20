#ifndef VIDEO_H
#define VIDEO_H

#include "BaseMedia.h"
#include "IVisual.h"
#include "IPlayable.h"

// Video is a visual, playable media item.
// It stores name, duration, and description.
class Video : public BaseMedia, public IVisual, public IPlayable {
public:
    // Constructor: name, duration, description
    Video(const std::string& name, const std::string& duration, const std::string& description);

    // Destructor
    ~Video();

    // Print format: "Video: videoname, Duration: 5:00, Description: info1"
    void info() const override;
};

#endif // VIDEO_H
