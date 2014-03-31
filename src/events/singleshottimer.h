#pragma once

#include "timer.h"


class SingleShotTimer : public Timer {
public:
    SingleShotTimer(float interval, const std::shared_ptr<Callback>& callback);

    virtual bool isDead() override;


protected:
    bool m_ticking;

    virtual void specialOnCallback() override;
};

