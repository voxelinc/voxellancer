#include "eventpoll.h"


EventPoll::EventPoll(const Callback& callback):
    m_callback(callback),
    m_active(true)
{

}

EventPoll::~EventPoll() = default;

bool EventPoll::isActive() const {
    return m_active;
}

void EventPoll::setActive(bool active) {
    m_active = active;
}

void EventPoll::update(float deltaSec) {
    if (!m_active) {
        return;
    }
    if (poll()) {
        doCallback();
        specialOnCallback();
    }
}

void EventPoll::doCallback() {
    m_callback.call();
}

void EventPoll::specialOnCallback() {

}

void EventPoll::doSpawn() {
    universe()->addFunctionalObject();
}
