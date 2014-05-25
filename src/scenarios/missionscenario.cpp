#include "missionscenario.h"

#include "missions/mission.h"

#include "player.h"

#include "resource/worldobjectbuilder.h"

#include "worldobject/worldobjectinfo.h"

#include "world/world.h"
#include "world/god.h"
#include "worldobject/ship.h"


MissionScenario::MissionScenario(GamePlay* gamePlay, const std::string& path):
    BaseScenario(gamePlay),
    m_mission(new Mission(path))
{
    World::instance()->addElement(m_mission);
}

void MissionScenario::populateWorld() {
    Ship *playerShip = WorldObjectBuilder("mox").buildShip();
    playerShip->transform().setPosition(glm::vec3(0, 0, 10));
    playerShip->info().setName("mox");
    m_world->god().scheduleSpawn(playerShip);

    World::instance()->player().setShip(playerShip);

    m_mission->start();
}

