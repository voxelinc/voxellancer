#pragma once

#include "timer.h"


class SingleShotTimer: public Timer {
public:
    SingleShotTimer(float interval, const std::function<void()>& target);

    virtual bool ticking() const override;


protected:
    bool m_ticking;

    virtual void onFired() override;
};

