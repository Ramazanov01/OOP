#ifndef NONPLAYABLE_H
#define NONPLAYABLE_H

class Non_playable {
public:
    virtual ~Non_playable() = default;
    // Oynatılamayan nesneler görüntülenirken bu metot çağrılacak
    virtual void view() const = 0;
};

#endif // NONPLAYABLE_H
