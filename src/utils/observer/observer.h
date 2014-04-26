#pragma once

#include <unordered_set>


class Event;
class Observable;

class Observer {
public:
    Observer();
    virtual ~Observer();

    bool observes(Observable* observable);

    void observe(Observable* observable);
    void stopObserving(Observable* observable);

    void notify(Event* event);


protected:
    std::unordered_set<Observable*> m_subjects;

    virtual void onEvent(Event* event);
};

