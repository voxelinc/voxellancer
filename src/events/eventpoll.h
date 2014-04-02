#pragma once

#include <functional>
#include <memory>

#include "scripting/scriptable.h"

#include "utils/handle/handleowner.h"


class EventPoll: public Scriptable, public HandleOwner {
public:
    EventPoll(const std::function<void()>& callback);
    ~EventPoll();

    /*
        Return true if the poll won't fire anymore
    */
    virtual bool isDead();

    virtual void update(float deltaSec);

    bool isActive() const;
    void setActive(bool active);


protected:
    std::function<void()> m_callback;
    bool m_active;

    void doCallback();
    virtual bool poll() = 0;
    virtual void specialOnCallback();
};

