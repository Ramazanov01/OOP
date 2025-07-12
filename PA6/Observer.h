#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default;
    // Dataset’de değişiklik olunca çağrılacak
    virtual void update() = 0;
};

#endif // OBSERVER_H
