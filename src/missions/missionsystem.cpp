#include "missionsystem.h"

#include "mission.h"


MissionSystem::MissionSystem() {

}

MissionSystem::~MissionSystem() = default;

void MissionSystem::update(float deltaSec) {
    for (std::unique_ptr<Mission>& mission : m_missions) {
        mission->update(deltaSec);
    }
}

void MissionSystem::addMission(Mission* mission) {
    m_missions.push_back(std::unique_ptr<Mission>(mission));
    mission->start();
}
