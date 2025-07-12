#ifndef VIEWER_H
#define VIEWER_H

#include "Observer.h"
#include "Dataset.h"
#include "NonPlayable.h"
#include <vector>
#include <string>

class Viewer : public Observer {
private:
    std::vector<Non_playable*> viewlist;
    int currentIndex;
    Dataset* dataset;

public:
    Viewer();
    void setDataset(Dataset* ds);

    // Dataset’teki değişimleri dinle
    void update() override;

    // Listeyi göster
    void show_list() const;

    // Şu an görüntülenen item’ı döndür
    Non_playable* currently_viewing();

    // Bir sonraki “text” veya “image” itemına geç
    void next(const std::string &type);

    // Bir önceki “text” veya “image” itemına geç
    void previous(const std::string &type);

private:
    bool matchesType(Non_playable* obj, const std::string &type) const;
};

#endif // VIEWER_H
