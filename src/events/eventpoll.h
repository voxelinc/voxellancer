#pragma once

#include <functional>
#include <memory>

#include "scripting/scriptable.h"

#include "utils/handle/handle.h"


class EventPoll: public Scriptable {
public:
    EventPoll(const std::function<void()>& callback);
    ~EventPoll();

    virtual ScriptableType scriptableType() const override;

    /*
        Return true if the poll won't fire anymore
    */
    virtual bool isDead() const;
    virtual void update(float deltaSec);

    bool active() const;
    void setActive(bool active);

    Handle<EventPoll>& handle();

protected:
    std::function<void()> m_callback;
    Handle<EventPoll> m_handle;
    bool m_active;

    void doCallback();
    virtual bool poll() = 0;
    virtual void specialOnCallback();
};

