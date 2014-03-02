#include "eventpoll.h"

#include <iostream>


EventPoll::EventPoll(const std::function<void()>& callback):
    m_callback(callback),
    m_handle(Handle<EventPoll>(this)),
    m_active(true)
{

}

EventPoll::~EventPoll() {
    m_handle.invalidate();
}

ScriptableType EventPoll::scriptableType() const {
    return ScriptableType::EventPoll;
}

bool EventPoll::dead() const {
    return false;
}

bool EventPoll::active() const {
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
        callback();
        onCallbacked();
    }
}

void EventPoll::callback() {
    m_callback();
}

Handle<EventPoll>& EventPoll::handle() {
    return m_handle;
}

void EventPoll::onCallbacked() {

}

