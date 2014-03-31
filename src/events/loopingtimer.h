#pragma once

#include "timer.h"


class LoopingTimer : public Timer {
public:
    LoopingTimer(float interval, const std::shared_ptr<Callback>& callback);
};

