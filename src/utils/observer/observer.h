#pragma once




class Observer {
public:
    Observer();

    virtual void notify(Event* event);
};
