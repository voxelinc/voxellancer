#include "missionsystem.h"

#include <iostream>

#include "mission.h"


MissionSystem::MissionSystem() {

}

MissionSystem::~MissionSystem() = default;

void MissionSystem::update(float deltaSec) {
    for (auto i = m_missions.begin(); i != m_missions.end(); ++i) {
        Mission* mission = i->get();

        mission->update(deltaSec);

        if (!mission->active()) {
            i = m_missions.erase(i);
        }
    }
}

void MissionSystem::addMission(Mission* mission) {
    m_missions.push_back(std::unique_ptr<Mission>(mission));
    mission->start();
}

