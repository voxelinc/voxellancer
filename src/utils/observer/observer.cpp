#include "observer.h"

#include "observable.h"


Observer::Observer() = default;

Observer::~Observer() {
    for (Observable* observable : m_subjects) {
        observable->deregisterObserver(this);
    }
}

bool Observer::observes(Observable* observable) {
    return m_subjects.find(observable) != m_subjects.end();
}

void Observer::observe(Observable* observable) {
    m_subjects.insert(observable);
    observable->registerObserver(this);
}

void Observer::stopObserving(Observable* observable) {
    m_subjects.erase(observable);
    observable->deregisterObserver(this);
}

void Observer::notify(Event* event) {
    onEvent(event);
}

void Observer::onEvent(Event* event) {

}

