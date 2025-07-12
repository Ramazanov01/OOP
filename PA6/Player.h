#ifndef PLAYER_H
#define PLAYER_H

#include "Observer.h"
#include "Dataset.h"
#include "Playable.h"
#include <vector>
#include <string>

class Player : public Observer {
private:
    std::vector<Playable*> playlist;
    int currentIndex;
    Dataset* dataset;

public:
    Player();
    void setDataset(Dataset* ds);

    // Observer arayüzünden (Subject’teki değişimleri yakalamak için)
    void update() override;

    // Çalma listesini göster
    void show_list() const;

    // Şu an hangi item çalınıyor?
    Playable* currently_playing();

    // Tip bilgisi ("audio" veya "video") vererek sıradaki item’a geç
    void next(const std::string &type);

    // Tip bilgisi vererek önceki item’a geç
    void previous(const std::string &type);

private:
    // O anki öğenin sesi mi, videosu mu kontrol et
    bool matchesType(Playable* obj, const std::string &type) const;
};

#endif // PLAYER_H
