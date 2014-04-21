#include "eventpoll.h"


EventPoll::EventPoll(const Callback& callback):
    m_callback(callback),
    m_handle(Handle<EventPoll>(this)),
    m_active(true)
{

}

EventPoll::~EventPoll() {
    m_handle.invalidate();
}

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
    m_callback.call();
}

Handle<EventPoll>& EventPoll::handle() {
    return m_handle;
}

void EventPoll::specialOnCallback() {

}

