#ifndef PLAYABLE_H
#define PLAYABLE_H

#include <string>

class Playable {
protected:
    std::string duration;

public:
    Playable(const std::string &dur);
    virtual ~Playable();

    // Oynatılabilir nesneler oynatıldığında bu metot çağrılacak
    virtual void play() const = 0;
    std::string getDuration() const;
};

#endif // PLAYABLE_H
