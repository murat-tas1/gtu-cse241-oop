#include <iostream>
#include <algorithm>
#include "Player.h"
#include "BaseMedia.h"
#include "Audio.h"
#include "Video.h"

// Initialize currentIndex = -1 (no current item)
Player::Player()
    : currentIndex(-1) {}

Player::~Player() {
    playList.clear();  // We do not delete items here; Dataset owns them
}

// Check if m is Audio when type="audio", or Video when type="video"
bool Player::matchesType(BaseMedia* m, const std::string& type) const {
    if (type == "audio") {
        return (dynamic_cast<Audio*>(m) != nullptr);
    } else if (type == "video") {
        return (dynamic_cast<Video*>(m) != nullptr);
    }
    return false;
}

// Called when Dataset adds a new item.
// If that item is playable, add it to playList.
void Player::updateAdd(BaseMedia* m) {
    IPlayable* ip = dynamic_cast<IPlayable*>(m);
    if (ip != nullptr) {
        playList.push_back(m);
        if (currentIndex < 0) {
            currentIndex = 0;  // Start playing first added item
        }
    }
}

// Called when Dataset removes an item.
// If that item is in playList, remove it and adjust currentIndex.
void Player::updateRemove(BaseMedia* m) {
    IPlayable* ip = dynamic_cast<IPlayable*>(m);
    if (ip != nullptr) {
        auto it = std::find(playList.begin(), playList.end(), m);
        if (it != playList.end()) {
            int removedIndex = static_cast<int>(std::distance(playList.begin(), it));
            playList.erase(it);

            if (playList.empty()) {
                currentIndex = -1;  // No items left
            } else {
                if (removedIndex < currentIndex) {
                    currentIndex--;  // Shift index left
                } else if (removedIndex == currentIndex) {
                    // If we removed the current item, try to move to next
                    std::string type;
                    if (dynamic_cast<Audio*>(m) != nullptr) type = "audio";
                    else if (dynamic_cast<Video*>(m) != nullptr) type = "video";

                    try {
                        next(type);
                    } catch (...) {
                        currentIndex = -1;  // No next found
                    }
                }
            }
        }
    }
}

// Print all playable items in the playlist, one per line.
void Player::showList() const {
    std::cout << "Player Playlist:" << std::endl;
    if (playList.empty()) {
        std::cout << " (empty)" << std::endl;
        return;
    }
    for (auto m : playList) {
        m->info();  // Each media prints itself in the “Audio: …” or “Video: …” format
    }
}

// Return the currently playing media pointer (or nullptr if none)
BaseMedia* Player::currentlyPlaying() const {
    if (currentIndex < 0 || currentIndex >= static_cast<int>(playList.size())) {
        return nullptr;
    }
    return playList[currentIndex];
}

// Advance to the next item of the given type in a circular manner.
// If no next item is found, throw an exception.
void Player::next(const std::string& type) {
    if (playList.empty()) {
        throw std::runtime_error("Player: Playlist is empty, cannot go to next.");
    }

    int start = currentIndex;
    int n = static_cast<int>(playList.size());
    for (int offset = 1; offset < n; ++offset) {
        int idx = (start + offset) % n;
        if (matchesType(playList[idx], type)) {
            currentIndex = idx;
            return;
        }
    }
    throw std::runtime_error("Player: No next item of type '" + type + "'.");
}

// Move to the previous item of the given type (circular).
// If no previous item is found, throw an exception.
void Player::previous(const std::string& type) {
    if (playList.empty()) {
        throw std::runtime_error("Player: Playlist is empty, cannot go to previous.");
    }

    int start = currentIndex;
    int n = static_cast<int>(playList.size());
    for (int offset = 1; offset < n; ++offset) {
        int idx = (start - offset + n) % n;
        if (matchesType(playList[idx], type)) {
            currentIndex = idx;
            return;
        }
    }
    throw std::runtime_error("Player: No previous item of type '" + type + "'.");
}
