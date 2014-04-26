#include "missionstatepoll.h"


MissionStatePoll::MissionStatePoll(Mission& mission, MissionState state, const Callback& callback):
    EventPoll(callback),
    m_mission(&mission),
    m_state(state),
    m_dead(false)
{
}

bool MissionStatePoll::isDead() {
    return m_dead;
}

bool MissionStatePoll::poll() {
    return m_mission->state() == m_state;
}

void MissionStatePoll::specialOnCallback() {
    m_dead = true;
}

