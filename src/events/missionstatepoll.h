#pragma once

#include "missions/mission.h"

#include "utils/handle/handle.h"

#include "eventpoll.h"


class MissionStatePoll : public EventPoll {
public:
    MissionStatePoll(const Handle<Mission>& mission, MissionState state, const std::function<void()>& callback);

    virtual bool isDead() override;


protected:
    Handle<Mission> m_mission;
    MissionState m_state;
    bool m_dead;


    virtual bool poll() override;
    virtual void specialOnCallback() override;
};
