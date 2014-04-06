#include "friendlyfirescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/character.h"
#include "ai/basictasks/flytotask.h"
#include "ai/grouptasks/patrolwaypointstask.h"
#include "ai/grouptasks/defendareatask.h"
#include "ai/basictasks/formationmembertask.h"
#include "ai/squadlogic.h"
#include "ai/squad.h"

#include "equipment/engineslot.h"
#include "equipment/hardpoint.h"
#include "equipment/weapons/gun.h"

#include "factions/factionmatrix.h"

#include "resource/worldobjectbuilder.h"

#include "worldobject/ship.h"
#include "sound/soundmanager.h"
#include "gamestate/gameplay/gameplay.h"
#include "world/world.h"
#include "voxel/voxel.h"
#include "world/god.h"
#include "player.h"
#include "worldobject/worldobjectinfo.h"


FriendlyFireScenario::FriendlyFireScenario(GamePlay* gamePlay) :
    BaseScenario(gamePlay)
{
}

void FriendlyFireScenario::populateWorld() {
    glow::debug("Create WorldObjects");

    Ship *victim = WorldObjectBuilder("mox").buildShip();
    victim->transform().setPosition(glm::vec3(0, 0, 200));
    victim->info().setName("member");
    victim->info().setShowOnHud(true);
    victim->info().setCanLockOn(true);
    victim->character()->setFaction(World::instance()->factionMatrix().policeFaction());
    m_world->god().scheduleSpawn(victim);

    std::shared_ptr<Squad> attacker = std::make_shared<Squad>();
    attacker->setTask(std::make_shared<DefendAreaTask>(*attacker,
        std::list<glm::vec3>{glm::vec3(0, 0, 0)}, 500.0f));
    Ship* pirate = WorldObjectBuilder("piratelight").buildShip();
    pirate->transform().setPosition(glm::vec3(0, 0, -200));
    pirate->transform().setOrientation(glm::quat(glm::vec3(0, 0, 1)));
    pirate->info().setName("pirate");
    pirate->info().setShowOnHud(true);
    pirate->info().setCanLockOn(true);
    pirate->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
    pirate->squadLogic()->joinSquad(attacker);
    m_world->god().scheduleSpawn(pirate);


    Ship *playerShip = WorldObjectBuilder("bc304").buildShip();
    playerShip->transform().setPosition(glm::vec3(0, 0, 10));
    playerShip->info().setName("player");
    playerShip->info().setShowOnHud(false);
    m_world->god().scheduleSpawn(playerShip);
    World::instance()->player().setShip(playerShip);

    glow::debug("Initial spawn");
    m_world->god().spawn();
}