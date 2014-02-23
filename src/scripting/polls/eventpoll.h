#pragma once

#include <memory>


class EventPoll {
public:
    EventPoll(const std::function<void()>& callback);

    virtual void update(float deltaSec) = 0;


protected:
    std::function<void()> m_callback;
};

