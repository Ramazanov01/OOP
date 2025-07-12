#ifndef DATASET_H
#define DATASET_H

#include "MediaObject.h"
#include "Observer.h"
#include <vector>
#include <algorithm> // std::find

// Öne bildirimler
class Playable;
class Non_playable;

class Dataset {
private:
    std::vector<MediaObject*> objects;
    std::vector<Observer*> observers;

public:
    ~Dataset();

    // YENİ bir media nesnesi ekle
    void add(MediaObject* obj);

    // Varolan bir media nesnesini sil
    void remove(MediaObject* obj);

    // Gözlemci kaydet
    void registerObserver(Observer* obs);

    // Gözlemci sil
    void removeObserver(Observer* obs);

    // Gözlemcilere haber ver
    void notifyObservers();

    // Şu anki playable (Audio/Video) nesnelerin listesini döndür
    std::vector<Playable*> getPlayableObjects() const;

    // Şu anki non-playable (Image/Text) nesnelerin listesini döndür
    std::vector<Non_playable*> getNonPlayableObjects() const;
};

#endif // DATASET_H
