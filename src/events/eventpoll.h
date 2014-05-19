#pragma once

#include <memory>

#include "utils/callback.h"

#include "universe/functionalobject.h"


class EventPoll: public FunctionalObject {
public:
    EventPoll(const Callback& callback);
    virtual ~EventPoll();

    virtual void update(float deltaSec) override;

    bool isActive() const;
    void setActive(bool active);


protected:
    Callback m_callback;
    bool m_active;

    virtual bool poll() = 0;
    virtual void specialOnCallback();
};

