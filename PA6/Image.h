#ifndef IMAGE_H
#define IMAGE_H

#include "MediaObject.h"
#include "Visual.h"
#include "NonPlayable.h"
#include <string>

class Image : public MediaObject, public Visual, public Non_playable {
private:
    std::string dimension;

public:
    Image(const std::string &name, const std::string &dim, const std::string &info);

    void info_display() const override;  // MediaObject’den gelen saf sanal (pure virtual) metod
    void display() const override;       // Visual arayüzünden gelen metod
    void view() const override;          // Non_playable arayüzünden gelen metod

    std::string getDimension() const;
};

#endif // IMAGE_H
