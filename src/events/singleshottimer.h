#pragma once

#include "timer.h"


class SingleShotTimer : public Timer {
public:
    SingleShotTimer(float interval, const std::function<void()>& callback);

    virtual bool isDead() override;


protected:
    bool m_ticking;

    virtual void specialOnCallback() override;
};

