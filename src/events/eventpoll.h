#pragma once

#include <memory>

#include "scripting/scriptable.h"

#include "utils/callback.h"
#include "utils/handle/handle.h"


class EventPoll: public Scriptable {
public:
    EventPoll(const std::shared_ptr<Callback>& callback);
    ~EventPoll();

    /*
        Return true if the poll won't fire anymore
    */
    virtual bool isDead();
    virtual void update(float deltaSec);

    bool isActive() const;
    void setActive(bool active);

    Handle<EventPoll>& handle();

protected:
    std::shared_ptr<Callback> m_callback;
    Handle<EventPoll> m_handle;
    bool m_active;

    void doCallback();
    virtual bool poll() = 0;
    virtual void specialOnCallback();
};

