#include <iostream>
#include <algorithm>
#include "Viewer.h"
#include "BaseMedia.h"
#include "Image.h"
#include "Text.h"

// Initialize currentIndex = -1 (no current item)
Viewer::Viewer()
    : currentIndex(-1) {}

Viewer::~Viewer() {
    viewList.clear();  // Dataset deletes the actual BaseMedia* objects
}

// Check if m is Image when type="image", or Text when type="text"
bool Viewer::matchesType(BaseMedia* m, const std::string& type) const {
    if (type == "image") {
        return (dynamic_cast<Image*>(m) != nullptr);
    } else if (type == "text") {
        return (dynamic_cast<Text*>(m) != nullptr);
    }
    return false;
}

// Called when Dataset adds a new item.
// If that item is non-playable, add it to viewList.
void Viewer::updateAdd(BaseMedia* m) {
    INonPlayable* inp = dynamic_cast<INonPlayable*>(m);
    if (inp != nullptr) {
        viewList.push_back(m);
        if (currentIndex < 0) {
            currentIndex = 0;  // Start viewing first added item
        }
    }
}

// Called when Dataset removes an item.
// If that item is in viewList, remove it and adjust currentIndex.
void Viewer::updateRemove(BaseMedia* m) {
    INonPlayable* inp = dynamic_cast<INonPlayable*>(m);
    if (inp != nullptr) {
        auto it = std::find(viewList.begin(), viewList.end(), m);
        if (it != viewList.end()) {
            int removedIndex = static_cast<int>(std::distance(viewList.begin(), it));
            viewList.erase(it);

            if (viewList.empty()) {
                currentIndex = -1;  // No items left
            } else {
                if (removedIndex < currentIndex) {
                    currentIndex--;  // Shift index left
                } else if (removedIndex == currentIndex) {
                    // If we removed the current item, try to move to next
                    std::string type;
                    if (dynamic_cast<Image*>(m) != nullptr) type = "image";
                    else if (dynamic_cast<Text*>(m) != nullptr)  type = "text";

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

// Print all non-playable items in the viewList, one per line.
void Viewer::showList() const {
    std::cout << "Viewer List:" << std::endl;
    if (viewList.empty()) {
        std::cout << " (empty)" << std::endl;
        return;
    }
    for (auto m : viewList) {
        m->info();  // Each media prints itself in “Image: …” or “Text: …” format
    }
}

// Return the currently viewing media pointer (or nullptr if none)
BaseMedia* Viewer::currentlyViewing() const {
    if (currentIndex < 0 || currentIndex >= static_cast<int>(viewList.size())) {
        return nullptr;
    }
    return viewList[currentIndex];
}

// Advance to the next item of the given type in a circular manner.
// If no next item is found, throw an exception.
void Viewer::next(const std::string& type) {
    if (viewList.empty()) {
        throw std::runtime_error("Viewer: viewList is empty, cannot go to next.");
    }

    int start = currentIndex;
    int n = static_cast<int>(viewList.size());
    for (int offset = 1; offset < n; ++offset) {
        int idx = (start + offset) % n;
        if (matchesType(viewList[idx], type)) {
            currentIndex = idx;
            return;
        }
    }
    throw std::runtime_error("Viewer: No next item of type '" + type + "'.");
}

// Move to the previous item of the given type (circular).
// If no previous item is found, throw an exception.
void Viewer::previous(const std::string& type) {
    if (viewList.empty()) {
        throw std::runtime_error("Viewer: viewList is empty, cannot go to previous.");
    }

    int start = currentIndex;
    int n = static_cast<int>(viewList.size());
    for (int offset = 1; offset < n; ++offset) {
        int idx = (start - offset + n) % n;
        if (matchesType(viewList[idx], type)) {
            currentIndex = idx;
            return;
        }
    }
    throw std::runtime_error("Viewer: No previous item of type '" + type + "'.");
}
