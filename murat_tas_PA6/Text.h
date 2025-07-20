#ifndef TEXT_H
#define TEXT_H

#include "BaseMedia.h"
#include "INonVisual.h"
#include "INonPlayable.h"

// Text is a non-visual, non-playable media item.
// It stores a name and a description (content).
class Text : public BaseMedia, public INonVisual, public INonPlayable {
public:
    // Constructor: name and content
    Text(const std::string& name, const std::string& content);

    // Destructor
    ~Text();

    // Print in required format: "Text: textname, Description: content"
    void info() const override;
};

#endif // TEXT_H
