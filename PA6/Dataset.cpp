#include "Dataset.h"
#include "Playable.h"
#include "NonPlayable.h"
#include <iostream>

// Destructor: delete all MediaObject pointers stored in 'objects'
Dataset::~Dataset() {
    for (auto obj : objects) {
        delete obj;
    }
}

// Add a new MediaObject to the dataset, then notify all observers
void Dataset::add(MediaObject* obj) {
    objects.push_back(obj);
    std::cout << "Added " << obj->getName() << " to dataset." << std::endl;
    notifyObservers();
}

// Remove a MediaObject from the dataset if it exists, then notify observers
void Dataset::remove(MediaObject* obj) {
    auto it = std::find(objects.begin(), objects.end(), obj);
    if (it != objects.end()) {
        std::cout << "Removed " << obj->getName() << " from dataset." << std::endl;
        objects.erase(it);
        notifyObservers();
    }
}

// Register a new Observer, then immediately call its update() for initial sync
void Dataset::registerObserver(Observer* obs) {
    observers.push_back(obs);
    obs->update();
}

// Remove an existing Observer so it no longer receives updates
void Dataset::removeObserver(Observer* obs) {
    auto it = std::find(observers.begin(), observers.end(), obs);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

// Notify all registered Observers by calling their update() method
void Dataset::notifyObservers() {
    for (auto obs : observers) {
        obs->update();
    }
}

// Return a vector of all Playable objects currently stored
std::vector<Playable*> Dataset::getPlayableObjects() const {
    std::vector<Playable*> playables;
    for (auto obj : objects) {
        Playable* p = dynamic_cast<Playable*>(obj);
        if (p) {
            playables.push_back(p);
        }
    }
    return playables;
}

// Return a vector of all Non_playable objects currently stored
std::vector<Non_playable*> Dataset::getNonPlayableObjects() const {
    std::vector<Non_playable*> nonPlayables;
    for (auto obj : objects) {
        Non_playable* np = dynamic_cast<Non_playable*>(obj);
        if (np) {
            nonPlayables.push_back(np);
        }
    }
    return nonPlayables;
}
