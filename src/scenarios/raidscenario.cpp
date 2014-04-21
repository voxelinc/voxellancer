#include "raidscenario.h"

#include "ai/character.h"
#include "ai/squadlogic.h"
#include "ai/grouptasks/defendareatask.h"
#include "ai/grouptasks/raidsectortask.h"
#include "ai/squad.h"

#include "factions/faction.h"
#include "factions/factionmatrix.h"

#include "resource/worldobjectbuilder.h"

#include "worldobject/ship.h"

#include "world/god.h"
#include "world/spawnhelper.h"
#include "world/world.h"

#include "player.h"


RaidScenario::RaidScenario(GamePlay* gamePlay):
    BaseScenario(gamePlay)
{

}

void RaidScenario::populateWorld() {
    Ship* playerShip = m_spawnHelper->spawnShip("f302", glm::vec3(0, 0, 10), m_world->factionMatrix().playerFaction());
    World::instance()->player().setShip(playerShip);

    std::shared_ptr<Squad> squadA = std::make_shared<Squad>();
    squadA->setTask(std::make_shared<RaidSectorTask>(*squadA));

    for (int i = 0; i < 9; i++) {
        Ship* ship = m_spawnHelper->spawnShip("piratelight", glm::vec3(i * 20, i * 30, i * -100 - 100), m_world->factionMatrix().pirateFaction());
        ship->squadLogic()->joinSquad(squadA);
    }
}

