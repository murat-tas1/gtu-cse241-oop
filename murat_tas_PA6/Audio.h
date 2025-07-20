#ifndef AUDIO_H
#define AUDIO_H

#include "BaseMedia.h"
#include "INonVisual.h"
#include "IPlayable.h"

// Audio is a non-visual, playable media item.
// It stores name, duration, and description.
class Audio : public BaseMedia, public INonVisual, public IPlayable {
public:
    // Constructor: name, duration (e.g., "3:00"), description
    Audio(const std::string& name, const std::string& duration, const std::string& description);

    // Destructor
    ~Audio();

    // Print format: "Audio: audioname, Duration: 3:00, Description: info1"
    void info() const override;
};

#endif // AUDIO_H
