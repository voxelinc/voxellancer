#include "eventpoller.h"

#include <iostream>

#include "eventpoll.h"

#include "scripting/scriptengine.h"

#include "world/world.h"


EventPoller::EventPoller()
{

}

EventPoller::~EventPoller() = default;

void EventPoller::addPoll(std::shared_ptr<EventPoll> eventPoll) {
    m_eventPolls.push_back(eventPoll);
    World::instance()->scriptEngine().registerScriptable(eventPoll.get());
}

void EventPoller::removePoll(std::shared_ptr<EventPoll> eventPoll) {
    m_eventPolls.remove_if([&](std::shared_ptr<EventPoll>& eventPollPtr) { return eventPollPtr == eventPoll; });
    World::instance()->scriptEngine().unregisterScriptable(eventPoll.get());
}

void EventPoller::update(float deltaSec) {
    for (auto iter = m_eventPolls.begin(); iter != m_eventPolls.end();) {
        EventPoll* poll = iter->get();
        poll->update(deltaSec);
        if (poll->dead()) {
            iter = m_eventPolls.erase(iter);
        } else {
            ++iter;
        }
    }
}
