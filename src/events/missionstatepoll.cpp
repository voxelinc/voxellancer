#include "missionstatepoll.h"


MissionStatePoll::MissionStatePoll(Mission& mission, MissionState state, const Callback& callback):
    EventPoll(callback),
    m_mission(&mission),
    m_state(state),
    m_fired(false)
{
}

bool MissionStatePoll::poll() {
    if (m_fired) {
        return false;
    } else {
        return m_mission->state() == m_state;
    }
}

void MissionStatePoll::specialOnCallback() {
    EventPoll::specialOnCallback();
    m_fired = true;
    unspawn();
}

