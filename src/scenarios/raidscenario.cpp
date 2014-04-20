#include "raidscenario.h"

#include "ai/character.h"
#include "ai/squadlogic.h"
#include "ai/grouptasks/defendareatask.h"
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
    Ship* playerShip = m_spawnHelper->spawnShip("startortress", glm::vec3(0, 0, 10), m_world->factionMatrix().playerFaction());
    World::instance()->player().setShip(playerShip);

    std::shared_ptr<Squad> squadA = std::make_shared<Squad>();
    squadA->setTask(std::make_shared<DefendAreaTask>(*squadA,
        std::list<glm::vec3>{
            glm::vec3(900, 0, 0),
            glm::vec3(1500, 0, 0),
            glm::vec3(1400, 500, 0),
        }, 500.0f));

    Ship* normandy = m_spawnHelper->spawnShip("normandy", glm::vec3(0, 0, -100), m_world->factionMatrix().pirateFaction());
    normandy->squadLogic()->joinSquad(squadA);
}

