#ifndef NONVISUAL_H
#define NONVISUAL_H

class Non_Visual {
public:
    virtual ~Non_Visual() = default;
    // Görsel olmayan nesneler işlenirken bu metot çağrılacak
    virtual void process() const = 0;
};

#endif // NONVISUAL_H
