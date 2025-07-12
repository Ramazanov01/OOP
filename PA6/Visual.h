#ifndef VISUAL_H
#define VISUAL_H

class Visual {
public:
    virtual ~Visual() = default;
    // Görsel nesneler gösterildiğinde bu metot çağrılacak
    virtual void display() const = 0;
};

#endif // VISUAL_H
