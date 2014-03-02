#include "eventpoller.h"

#include <iostream>

#include "eventpoll.h"

#include "scripting/scriptengine.h"

#include "world/world.h"


EventPoller::EventPoller()
{

}

EventPoller::~EventPoller() = default;

void EventPoller::addPoll(EventPoll* eventPoll) {
    m_eventPolls.push_back(std::unique_ptr<EventPoll>(eventPoll));
    World::instance()->scriptEngine().registerScriptable(eventPoll);
}

void EventPoller::removePoll(EventPoll* eventPoll) {
    m_eventPolls.remove_if([&](std::unique_ptr<EventPoll>& eventPollPtr) { return eventPollPtr.get() == eventPoll; });
    World::instance()->scriptEngine().unregisterScriptable(eventPoll);
}

void EventPoller::update(float deltaSec) {
    for (std::list<std::unique_ptr<EventPoll>>::iterator i = m_eventPolls.begin(); i != m_eventPolls.end(); ++i) {
        EventPoll* poll = i->get();
        poll->update(deltaSec);
        if (poll->dead()) {
            i = m_eventPolls.erase(i);
        }
    }
}
