#ifndef OBSERVER_H
#define OBSERVER_H

class BaseMedia;

// Observer is an interface for classes that want to be notified
// when items are added to or removed from the Dataset.
class Observer {
public:
    virtual ~Observer() {}

    // Called when a new BaseMedia* is added
    virtual void updateAdd(BaseMedia* m) = 0;

    // Called when a BaseMedia* is removed
    virtual void updateRemove(BaseMedia* m) = 0;
};

#endif // OBSERVER_H
