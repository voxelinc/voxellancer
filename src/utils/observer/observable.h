#pragma once

#include <unordered_set>


class Event;
class Observer;

class Observable {
public:
    Observable();
    virtual ~Observable();

    void registerObserver(Observer* observer);
    void deregisterObserver(Observer* observer);


protected:
    std::unordered_set<Observer*> m_observers;

    void notifyAll(Event* event);
};
