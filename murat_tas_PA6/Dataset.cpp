#include <algorithm> //for using std::remove ,std::find
#include "Dataset.h"
#include "BaseMedia.h"

// Constructor (empty)
Dataset::Dataset() {}

// Destructor: delete all media items, then clear vectors
Dataset::~Dataset() {
    for (auto m : items) {
        delete m;          // Free memory of each BaseMedia*
    }
    items.clear();         // Clear the list of items
    observers.clear();     // Clear the list of observers
}

// Add observer to list; it will now receive updates
void Dataset::registerObserver(Observer* o) {
    observers.push_back(o);
}

// Remove observer from list; it no longer receives updates
void Dataset::removeObserver(Observer* o) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), o),
        observers.end()
    );
}

// Add a media item: store it and notify all observers
void Dataset::add(BaseMedia* m) {
    items.push_back(m);
    for (auto obs : observers) {
        obs->updateAdd(m);
    }
}

// Remove a media item: erase from items, notify observers, then delete
void Dataset::remove(BaseMedia* m) {
    auto it = std::find(items.begin(), items.end(), m);
    if (it != items.end()) {
        items.erase(it);          // Remove from vector
        for (auto obs : observers) {
            obs->updateRemove(m); // Let each observer remove it from its own list
        }
        delete m;                 // Free memory
    }
}
