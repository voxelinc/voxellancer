#pragma once


class Event;

class Observer {
public:
    Observer();

    virtual void notify(Event* event);
};

