#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Observer.h"

class BaseMedia;
class Audio;
class Video;

// Player observes Dataset and keeps a list of playable items.
// It can show, navigate, and play next/previous items.
class Player : public Observer {
private:
    std::vector<BaseMedia*> playList;  // All playable items from Dataset
    int currentIndex;                   // Index of currently “playing” item

    // Helper: returns true if m matches the requested type (“audio” or “video”)
    bool matchesType(BaseMedia* m, const std::string& type) const;

public:
    // Constructor: initializes currentIndex to -1 (no item)
    Player();

    // Destructor: clear playList
    ~Player();

    // When a new media is added to Dataset, this is called
    void updateAdd(BaseMedia* m) override;

    // When a media is removed from Dataset, this is called
    void updateRemove(BaseMedia* m) override;

    // Print the full playlist
    void showList() const;

    // Return the current media pointer (or nullptr if none)
    BaseMedia* currentlyPlaying() const;

    // Move to next item of given type (“audio” or “video”)
    void next(const std::string& type);

    // Move to previous item of given type
    void previous(const std::string& type);
};

#endif // PLAYER_H
