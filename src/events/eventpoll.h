#pragma once

#include <memory>

#include "scripting/scriptable.h"

#include "utils/callback.h"
#include "utils/handle/handleowner.h"


class EventPoll: public Scriptable, public HandleOwner {
public:
    EventPoll(const Callback& callback);
    ~EventPoll();

    /*
        Return true if the poll won't fire anymore
    */
    virtual bool isDead();

    virtual void update(float deltaSec);

    bool isActive() const;
    void setActive(bool active);


protected:
    Callback m_callback;
    bool m_active;

    void doCallback();
    virtual bool poll() = 0;
    virtual void specialOnCallback();
};

