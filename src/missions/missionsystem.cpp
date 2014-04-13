#include "missionsystem.h"

#include "scripting/scriptengine.h"

#include "world/world.h"

#include "mission.h"


MissionSystem::MissionSystem()
{
}

MissionSystem::~MissionSystem() = default;

void MissionSystem::update(float deltaSec) {
/*    for (auto iter = m_missions.begin(); iter != m_missions.end(); ) {
        Mission* mission = *iter;

        mission->update(deltaSec);

        if (mission->state() != MissionState::Running) {
            iter = m_missions.erase(iter);
        } else {
            ++iter;
        }
    }*/
}

void MissionSystem::addMission(Mission* mission) {
    /*m_missions.push_back(mission);
    World::instance()->scriptEngine().registerScriptable(mission);
    mission->start();*/
}

void MissionSystem::removeMission(Mission* mission) {
/*    m_missions.remove(mission);
    World::instance()->scriptEngine().unregisterScriptable(mission);*/
}

