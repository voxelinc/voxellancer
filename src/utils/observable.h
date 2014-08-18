#pragma once

#include <list>


class Observer;

class Observable {
public:
    Observable();
    virtual ~Observable();

    void notifyObservers();
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);


protected:
    std::list<Observer*> m_observers;
};

