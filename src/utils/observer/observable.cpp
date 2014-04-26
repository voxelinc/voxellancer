#include "observable.h"

#include <cassert>

#include "observer.h"


Observable::Observable() {

}

Observable::~Observable() {
    for (Observer* observer : m_observers) {
        observer->stopObserving(this);
    }
}

void Observable::registerObserver(Observer* observer) {
    assert(observer->observes(this));
    m_observers.insert(observer);
}

void Observable::deregisterObserver(Observer* observer) {
    m_observers.erase(observer);
}

void Observable::notifyAll(Event* event) {
    for (Observer* observer : m_observers) {
        observer->notify(event);
    }
}

