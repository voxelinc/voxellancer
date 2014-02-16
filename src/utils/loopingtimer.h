#pragma once

#include "timer.h"


class LoopingTimer: public Timer {
public:
    LoopingTimer(float interval, const std::function<void()>& target);

    virtual bool ticking() const override;
};

