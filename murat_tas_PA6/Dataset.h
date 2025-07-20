#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include "Observer.h"

class BaseMedia;

// Dataset holds all media items and notifies observers on changes.
class Dataset {
private:
    std::vector<BaseMedia*> items;       // All media objects stored here
    std::vector<Observer*> observers;    // Observers to notify

public:
    // Constructor
    Dataset();

    // Destructor: deletes all media items and clears observer list
    ~Dataset();

    // Register a new observer (Player or Viewer)
    void registerObserver(Observer* o);

    // Remove an observer so it no longer gets updates
    void removeObserver(Observer* o);

    // Add a new media item and notify all observers
    void add(BaseMedia* m);

    // Remove a media item, notify observers, and delete it
    void remove(BaseMedia* m);
};

#endif // DATASET_H
