#include "observable.h"

#include "observer.h"

void Observable::addObserver(Observer* observer) {
    m_observers.push_back(observer);
}

void Observable::removeObserver(Observer* observer) {
    m_observers.remove(observer);
}

void Observable::notifyObservers() {
    for (Observer* observer : m_observers) {
        observer->updateObserver();
    }
}