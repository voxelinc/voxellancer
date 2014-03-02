#include "scriptedscenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/character.h"
#include "ai/basictasks/fighttask.h"

#include "equipment/hardpoint.h"
#include "equipment/engineslot.h"
#include "equipment/engine.h"
#include "equipment/weapon.h"
#include "equipment/weapons/gun.h"

#include "gamestate/gameplay/gameplay.h"

#include "resource/clustercache.h"
#include "resource/worldobjectbuilder.h"

#include "worldobject/ship.h"

#include "sound/soundmanager.h"

#include "world/world.h"
#include "world/god.h"

#include "player.h"
#include "ui/objectinfo.h"
#include "utils/randvec.h"

#include "scripting/scriptengine.h"
#include "scripting/gameplayscript.h"


ScriptedScenario::ScriptedScenario(GamePlay* gamePlay, const std::string& path):
    BaseScenario(gamePlay),
    m_script(new GamePlayScript(gamePlay, &World::instance()->scriptEngine()))
{
    m_script->load(path);
}

ScriptedScenario::~ScriptedScenario() = default;

void ScriptedScenario::populateWorld() {
    Ship *playerShip = WorldObjectBuilder("mox").buildShip();
    playerShip->transform().setPosition(glm::vec3(0, 0, 10));
    playerShip->objectInfo().setName("mox");
    playerShip->objectInfo().setShowOnHud(false);
    playerShip->objectInfo().setCanLockOn(false);
    m_world->god().scheduleSpawn(playerShip);
    m_gamePlay->player().setShip(playerShip);

    m_world->scriptEngine().addScript(m_script.get());
}
