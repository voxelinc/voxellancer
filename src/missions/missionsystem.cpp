#include "missionsystem.h"

#include <iostream>

#include "scripting/scriptengine.h"

#include "world/world.h"

#include "mission.h"


MissionSystem::MissionSystem()
{
}

MissionSystem::~MissionSystem() = default;

void MissionSystem::update(float deltaSec) {
    for (auto i = m_missions.begin(); i != m_missions.end(); ) {
        Mission* mission = i->get();

        mission->update(deltaSec);

        if (mission->state() != MissionState::Running) {
            i = m_missions.erase(i);
        } else {
            ++i;
        }
    }
}

void MissionSystem::addMission(Mission* mission) {
    m_missions.push_back(std::unique_ptr<Mission>(mission));
    World::instance()->scriptEngine().registerScriptable(mission);
    mission->start();
}

void MissionSystem::removeMission(Mission* mission) {
    m_missions.remove_if([&] (std::unique_ptr<Mission> &missionPtr) {
        return missionPtr.get() == mission;
    });
    World::instance()->scriptEngine().unregisterScriptable(mission);
}

