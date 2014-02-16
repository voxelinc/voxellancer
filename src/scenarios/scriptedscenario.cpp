#include "scriptedscenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/character.h"
#include "ai/basictasks/fighttask.h"

#include "resource/clustercache.h"

#include "worldobject/ship.h"

#include "game.h"
#include "world/world.h"
#include "world/god.h"
#include "utils/randvec.h"


ScriptedScenario::ScriptedScenario(Game* game, const std::string& path):
    BaseScenario(game),
    m_script(path)
{

}

void ScriptedScenario::populateWorld() {
    Ship *playerShip = new Ship();
    ClusterCache::instance()->fillObject(playerShip, "data/voxelcluster/basicship.csv");
    playerShip->setPosition(glm::vec3(0, 0, 10));
    playerShip->objectInfo().setName("basicship");
    playerShip->objectInfo().setShowOnHud(false);
    playerShip->objectInfo().setCanLockOn(false);
    world->god().scheduleSpawn(playerShip);
    m_game->player().setShip(playerShip);

    m_world->startScript(m_script);
}
