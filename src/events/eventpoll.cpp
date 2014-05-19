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
    if (m_callback.dead()) {
        scheduleRemoval();
    }

    if (!m_active) {
        return;
    }

    if (poll()) {
        m_callback.call();
        specialOnCallback();
    }
}

void EventPoll::specialOnCallback() {

}

