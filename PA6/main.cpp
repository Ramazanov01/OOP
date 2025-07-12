#include <iostream>
#include "Dataset.h"
#include "Player.h"
#include "Viewer.h"
#include "Image.h"
#include "Audio.h"
#include "Video.h"
#include "Text.h"

int main() {
    // 1) Create a single Dataset and two Players, two Viewers
    Dataset* ds = new Dataset();
    Player* p1 = new Player();
    Player* p2 = new Player();
    Viewer* v1 = new Viewer();
    Viewer* v2 = new Viewer();

    // 2) Link each observer to the same Dataset
    p1->setDataset(ds);
    p2->setDataset(ds);
    v1->setDataset(ds);
    v2->setDataset(ds);

    // 3) Register observers (so they receive updates)
    ds->registerObserver(p1);
    ds->registerObserver(p2);
    ds->registerObserver(v1);
    ds->registerObserver(v2);

    // 4) Add a few media objects to the Dataset
    ds->add(new Audio("A1", "1:00",    "InfoA1"));
    ds->add(new Video("V1", "2:00",    "InfoV1"));
    ds->add(new Image("I1", "100x100","InfoI1"));
    ds->add(new Text("T1", "InfoT1"));

    // 5) Show initial playlists for both Players
    std::cout << "\n--- Initial Playlists ---\n";
    p1->show_list();  // Expect: A1 [CURRENTLY PLAYING], V1
    p2->show_list();

    // 6) Show initial viewlists for both Viewers
    std::cout << "\n--- Initial Viewlists ---\n";
    v1->show_list();  // Expect: I1 [CURRENTLY VIEWING], T1
    v2->show_list();

    // 7) Demonstrate navigation:
    //    p1 jumps to the next video, p2 jumps to the next audio
    //    v1 jumps to the next image, v2 jumps to the next text
    p1->next("video");   // Should move from A1 to V1
    p2->next("audio");   // Should stay on A1 (only one audio)
    v1->next("image");   // Should stay on I1 (only one image)
    v2->next("text");    // Should stay on T1 (only one text)

    // 8) Print currently playing/viewing for p1 and v1
    MediaObject* curPlay = dynamic_cast<MediaObject*>(p1->currently_playing());
    std::cout << "\nCurrently playing (p1): ";
    curPlay->info_display();

    MediaObject* curView = dynamic_cast<MediaObject*>(v1->currently_viewing());
    std::cout << "Currently viewing (v1): ";
    curView->info_display();

    // 9) Remove p1’s currently playing item from the Dataset, then show updated playlists
    ds->remove(dynamic_cast<MediaObject*>(p1->currently_playing()));
    std::cout << "\n--- Playlists After Removing p1's Current ---\n";
    p1->show_list();  // Expect: V1 only
    p2->show_list();  // Expect: V1 only

    // 10) Remove p2 as an observer, then add a new Audio object
    ds->removeObserver(p2);
    ds->add(new Audio("A2", "1:30", "InfoA2"));

    std::cout << "\n--- Playlists After Removing p2 & Adding A2 ---\n";
    p1->show_list();  // Expect: V1, A2
    p2->show_list();  // Expect: V1 only (unchanged)

    // 11) Finally show viewlists again for completeness
    std::cout << "\n--- Final Viewlists (v1, v2) ---\n";
    v1->show_list();  // Expect: I1, T1 (unchanged by audio/video changes)
    v2->show_list();

    // 12) Clean up all allocated memory
    delete ds;
    delete p1;
    delete p2;
    delete v1;
    delete v2;

    return 0;
}
