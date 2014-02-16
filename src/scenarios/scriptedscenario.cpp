#include "scriptedscenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/character.h"
#include "ai/basictasks/fighttask.h"

#include "resource/clustercache.h"
#include "resource/worldobjectfactory.h"
#include "resource/worldobjectbuilder.h"

#include "worldobject/components/hardpoint.h"
#include "worldobject/components/engineslot.h"
#include "worldobject/components/engine.h"
#include "worldobject/components/weapon.h"
#include "worldobject/components/weapons/gun.h"
#include "worldobject/ship.h"

#include "sound/soundmanager.h"

#include "world/world.h"
#include "world/god.h"

#include "game.h"
#include "utils/randvec.h"

#include "scripting/scriptengine.h"
#include "scripting/gameplayscript.h"


ScriptedScenario::ScriptedScenario(Game* game, const std::string& path):
    BaseScenario(game),
    m_script(new GamePlayScript(World::instance()))
{
    m_script->load(path);
}

ScriptedScenario::~ScriptedScenario() = default;

void ScriptedScenario::populateWorld() {
    Ship *playerShip = WorldObjectBuilder("basicship").buildShip();
    playerShip->transform().setPosition(glm::vec3(0, 0, 10));
    playerShip->objectInfo().setName("basicship");
    playerShip->objectInfo().setShowOnHud(false);
    playerShip->objectInfo().setCanLockOn(false);
    m_world->god().scheduleSpawn(playerShip);
    m_game->player().setShip(playerShip);


    m_world->scriptEngine().startScript(m_script.get());
}
