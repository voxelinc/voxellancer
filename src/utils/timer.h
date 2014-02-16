#pragma once

#include <functional>


class Timer {
public:
    Timer(float interval, const std::function<void()>& target);

    /*
        Shall return false once the timer will never fire again,
        true otherwise
    */
    virtual bool ticking() const = 0;

    /*
        Calls the registered function once it is due
    */
    void update(float deltaSec);


protected:
    float m_interval;
    float m_countdown;
    std::function<void()> m_target;

    virtual void onFired();
};

