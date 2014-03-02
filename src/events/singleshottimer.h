#pragma once

#include "timer.h"


class SingleShotTimer : public Timer {
public:
    SingleShotTimer(float interval, const std::function<void()>& callback);

    virtual bool dead() const override;


protected:
    bool m_ticking;

    virtual void onCallbacked() override;
};

