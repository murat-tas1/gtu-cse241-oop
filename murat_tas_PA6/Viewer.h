#ifndef VIEWER_H
#define VIEWER_H

#include <vector>
#include <string>
#include "Observer.h"

class BaseMedia;
class Image;
class Text;

// Viewer observes Dataset and keeps a list of non-playable items.
// It can show, navigate, and display next/previous items.
class Viewer : public Observer {
private:
    std::vector<BaseMedia*> viewList;  // All non-playable items
    int currentIndex;                   // Index of currently “viewing” item

    // Helper: returns true if m matches requested type (“image” or “text”)
    bool matchesType(BaseMedia* m, const std::string& type) const;

public:
    // Constructor: set currentIndex = -1 (no item)
    Viewer();

    // Destructor: clear viewList
    ~Viewer();

    // Called when Dataset adds a new item
    void updateAdd(BaseMedia* m) override;

    // Called when Dataset removes an item
    void updateRemove(BaseMedia* m) override;

    // Print all non-playable items in the viewList
    void showList() const;

    // Return the currently viewing media pointer (or nullptr)
    BaseMedia* currentlyViewing() const;

    // Advance to next item of given type (“image” or “text”)
    void next(const std::string& type);

    // Move to previous item of given type
    void previous(const std::string& type);
};

#endif // VIEWER_H
