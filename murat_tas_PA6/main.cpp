#include <iostream>
#include "Dataset.h"
#include "Player.h"
#include "Viewer.h"
#include "Image.h"
#include "Audio.h"
#include "Video.h"
#include "Text.h"

int main() {
    // Create one shared Dataset
    Dataset* ds = new Dataset();

    // Create two Players and two Viewers
    Player* p1 = new Player();
    Player* p2 = new Player();
    Viewer* v1 = new Viewer();
    Viewer* v2 = new Viewer();

    // Register them so they get updates from the Dataset
    ds->registerObserver(p1);
    ds->registerObserver(p2);
    ds->registerObserver(v1);
    ds->registerObserver(v2);

    // --- Testing Empty Dataset ---
    std::cout << "--- Testing Empty Dataset ---" << std::endl;
    std::cout << "Player Playlist:" << std::endl;
    std::cout << " (empty)" << std::endl << std::endl;

    // --- Add initial media items ---
    // Add two Audios, one Video, two Images, and one Text
    ds->add(new Audio("audioname1", "3:00", "info1"));
    ds->add(new Audio("audioname2", "4:00", "info2"));
    ds->add(new Video("videoname1", "5:00", "info1"));
    ds->add(new Image("imagename1", "100x100", "info1"));
    ds->add(new Image("imagename2", "200x200", "info2"));
    ds->add(new Text("textname1", "info1"));

    // --- Player 1 List ---
    std::cout << "--- Player 1 List ---" << std::endl;
    p1->showList();   // Print all playable items for p1
    std::cout << std::endl;

    // --- Viewer 1 List ---
    std::cout << "--- Viewer 1 List ---" << std::endl;
    v1->showList();   // Print all non-playable items for v1
    std::cout << std::endl;

    // --- Currently Playing (Player 1) ---
    std::cout << "--- Currently Playing (Player 1) ---" << std::endl;
    if (auto cur = p1->currentlyPlaying()) {
        cur->info();  // Print the item currently playing
    } else {
        std::cout << "(none)" << std::endl;
    }
    std::cout << std::endl;

    // --- Currently Viewing (Viewer 1) ---
    std::cout << "--- Currently Viewing (Viewer 1) ---" << std::endl;
    if (auto curv = v1->currentlyViewing()) {
        curv->info();  // Print the item currently viewing
    } else {
        std::cout << "(none)" << std::endl;
    }
    std::cout << std::endl;

    // --- Next Audio (Player 1) ---
    try {
        p1->next("audio");  // Advance to next audio
        std::cout << "--- Next Audio (Player 1) ---" << std::endl;
        if (auto nextAudio = p1->currentlyPlaying()) {
            nextAudio->info();
        } else {
            std::cout << "(none)" << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;

    // --- Next Image (Viewer 1) ---
    try {
        v1->next("image");  // Advance to next image
        std::cout << "--- Next Image (Viewer 1) ---" << std::endl;
        if (auto nextImg = v1->currentlyViewing()) {
            nextImg->info();
        } else {
            std::cout << "(none)" << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;

    // --- Previous Video (Player 1) ---
    try {
        p1->previous("video");  // Move to previous video
        std::cout << "--- Previous Video (Player 1) ---" << std::endl;
        if (auto prevVid = p1->currentlyPlaying()) {
            prevVid->info();
        } else {
            std::cout << "(none)" << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;

    // --- Previous Image (Viewer 1) ---
    try {
        v1->previous("image");  // Move to previous image
        std::cout << "--- Previous Image (Viewer 1) ---" << std::endl;
        if (auto prevImg = v1->currentlyViewing()) {
            prevImg->info();
        } else {
            std::cout << "(none)" << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;

    // --- Removing Current Viewing Item (Viewer 1) ---
    if (auto toRemoveV = v1->currentlyViewing()) {
        std::cout << "--- Removing Current Viewing Item (Viewer 1) ---" << std::endl;
        toRemoveV->info();   // Print item to remove
        ds->remove(toRemoveV); // Remove from Dataset (and notify all observers)
    }
    std::cout << std::endl;

    // --- Viewer 1 List After Removal ---
    std::cout << "--- Viewer 1 List After Removal ---" << std::endl;
    v1->showList();  // Now one less non-playable item
    std::cout << std::endl;

    // --- Player 1 List After Removal ---
    std::cout << "--- Player 1 List After Removal ---" << std::endl;
    p1->showList();  // Player 1’s list also updated (if a playable item was removed)
    std::cout << std::endl;

    // --- Adding New Video ---
    ds->add(new Video("videoname2", "6:00", "info2"));
    std::cout << "--- Adding New Video ---" << std::endl;

    // --- Player 2 List After New Video ---
    std::cout << "--- Player 2 List After New Video ---" << std::endl;
    p2->showList();  // p2’s playlist updated with new video
    std::cout << std::endl;

    // --- Removing Viewer 1 Observer ---
    ds->removeObserver(v1);
    std::cout << "--- Removing Viewer 1 Observer ---" << std::endl;

    // --- Viewer 1 List (Should Not Update) ---
    std::cout << "--- Viewer 1 List (Should Not Update) ---" << std::endl;
    v1->showList();  // v1 no longer receives updates
    std::cout << std::endl;

    // --- Viewer 2 List (Should Update) ---
    std::cout << "--- Viewer 2 List (Should Update) ---" << std::endl;
    v2->showList();  // v2 still receives updates
    std::cout << std::endl;

    // Cleanup: unregister and delete observers, then delete the Dataset
    ds->removeObserver(p1);
    ds->removeObserver(p2);
    ds->removeObserver(v2);
    delete p1;
    delete p2;
    delete v1;
    delete v2;
    delete ds;

    return 0;
}
