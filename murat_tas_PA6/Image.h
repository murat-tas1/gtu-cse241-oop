// Image.h
#ifndef IMAGE_H
#define IMAGE_H

#include "BaseMedia.h"
#include "IVisual.h"
#include "INonPlayable.h"

// Image is a visual, non-playable media item.
// It stores name, dimensions, and a description (info).
class Image : public BaseMedia, public IVisual, public INonPlayable {
public:
    // This declaration must match *exactly* (types, order, and const‐qualifiers)
    Image(const std::string& name, 
          const std::string& dimensions, 
          const std::string& description);

    ~Image();

    // Print “Image: <name>, Dimensions: <dimensions>, Description: <description>”
    void info() const override;
};

#endif // IMAGE_H
