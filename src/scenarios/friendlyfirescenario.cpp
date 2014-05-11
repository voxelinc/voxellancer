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
#include "factions/factionrelation.h"

#include "resource/worldelementbuilder.h"

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

    Ship *victim = WorldElementBuilder("mox").buildShip();
    victim->transform().setPosition(glm::vec3(0, 0, 200));
    victim->info().setName("member");
    victim->info().setShowOnHud(true);
    victim->info().setCanLockOn(true);
    victim->character()->setFaction(World::instance()->factionMatrix().policeFaction());
    m_world->god().scheduleSpawn(victim);

    std::shared_ptr<Squad> attacker = std::make_shared<Squad>();
    attacker->setTask(std::make_shared<DefendAreaTask>(*attacker,
        std::list<glm::vec3>{glm::vec3(0, 0, 0)}, 500.0f));
    Ship* pirate = WorldElementBuilder("piratelight").buildShip();
    pirate->transform().setPosition(glm::vec3(0, -10, -200));
    pirate->transform().setOrientation(glm::quat(glm::vec3(0, 0, 1)));
    pirate->info().setName("pirate");
    pirate->info().setShowOnHud(true);
    pirate->info().setCanLockOn(true);
    pirate->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
    pirate->squadLogic()->joinSquad(attacker);
    m_world->god().scheduleSpawn(pirate);

    Ship *bigship = WorldElementBuilder("bc304").buildShip();
    bigship->transform().setPosition(glm::vec3(0, 0, 10));
    bigship->transform().setOrientation(glm::quat(glm::vec3(0, 0, 1)));
    bigship->info().setName("big");
    bigship->info().setShowOnHud(true);
    bigship->info().setShowOnHud(true);
    bigship->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
    m_world->god().scheduleSpawn(bigship);

    Ship *playerShip = WorldElementBuilder("basicship").buildShip();
    playerShip->transform().setPosition(glm::vec3(100, 0, 0));
    playerShip->transform().setOrientation(glm::quat(glm::vec3(0, glm::radians(70.0f), 0)));
    playerShip->info().setName("player");
    World::instance()->player().setShip(playerShip);
    m_world->god().scheduleSpawn(playerShip);

    World::instance()->factionMatrix().getRelationToPlayer(World::instance()->factionMatrix().pirateFaction()).setFriendliness(100);

    glow::debug("Initial spawn");
    m_world->god().spawn();
}
