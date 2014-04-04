#include "eventpoll.h"


EventPoll::EventPoll(const std::function<void()>& callback):
    m_callback(callback),
    m_active(true)
{

}

EventPoll::~EventPoll() = default;

bool EventPoll::isDead() {
    return false;
}

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
    m_callback();
}

void EventPoll::specialOnCallback() {

}

