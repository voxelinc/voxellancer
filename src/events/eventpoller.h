#pragma once

#include <memory>
#include <unordered_map>


class EventPoll;

class EventPoller {
public:
    EventPoller();
    ~EventPoller();

    void addPoll(std::shared_ptr<EventPoll> eventPoll);
    void removePoll(EventPoll* eventPoll);

    void update(float deltaSec);


protected:
    std::unordered_map<EventPoll*, std::shared_ptr<EventPoll>> m_eventPolls;
};

