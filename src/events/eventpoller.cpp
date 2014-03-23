#include "eventpoller.h"

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
    World::instance()->scriptEngine().unregisterScriptable(eventPoll);
    m_eventPolls.remove_if([&](std::unique_ptr<EventPoll>& eventPollPtr) {
        return eventPollPtr.get() == eventPoll;
    });
}

void EventPoller::update(float deltaSec) {
    for (auto iter = m_eventPolls.begin(); iter != m_eventPolls.end();) {
        EventPoll* poll = iter->get();
        poll->update(deltaSec);
        if (poll->isDead()) {
            iter = m_eventPolls.erase(iter);
        } else {
            ++iter;
        }
    }
}
