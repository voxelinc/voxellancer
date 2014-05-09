#pragma once

#include "timer.h"


class SingleShotTimer : public Timer {
public:
    SingleShotTimer(float interval, const Callback& callback);


protected:
    bool m_fired;

    virtual bool poll() override;
    virtual void specialOnCallback() override;
};

