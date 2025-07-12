#ifndef VIDEO_H
#define VIDEO_H

#include "MediaObject.h"
#include "Visual.h"
#include "Playable.h"
#include <string>

class Video : public MediaObject, public Visual, public Playable {
public:
    Video(const std::string &name, const std::string &dur, const std::string &info);

    void info_display() const override;  // MediaObject’den gelen saf sanal metod
    void display() const override;       // Visual arayüzündeki metod
    void play() const override;          // Playable arayüzündeki metod
};

#endif // VIDEO_H
