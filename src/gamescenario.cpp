#include "gamescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/characters/dummycharacter.h"
#include "ai/elevatedtasks/dummyelevatedtask.h"
#include "ai/basictask.h"
#include "ai/basictasks/flytotask.h"
#include "ai/elevatedtasks/patrolwaypointstask.h"

#include "resource/clustercache.h"
#include "resource/worldobjectfactory.h"
#include "resource/worldobjectequipmentfactory.h"

#include "worldobject/ship.h"
#include "worldobject/components/engineslot.h"
#include "worldobject/components/hardpoint.h"
#include "worldobject/components/weapons/gun.h"
#include "worldobject/components/engines/enginemk1.h"
#include "worldobject/components/engines/piratethruster.h"
#include "sound/soundmanager.h"
#include "game.h"
#include "world/world.h"
#include "voxel/voxel.h"
#include "world/god.h"


GameScenario::GameScenario() {

}

void GameScenario::populate(Game* game) {
    glowutils::AutoTimer t("Initialize Game");
    WorldObjectEquipmentFactory equipmentFactory;

    WorldObjectFactory worldObjectFactory;
    Ship *ship;

    glow::debug("Create world");
    World* world = World::instance();

    Ship *playerShip = worldObjectFactory.build<Ship>("basicship");
    playerShip->transform().setPosition(glm::vec3(0, 0, 50));

    playerShip->components().hardpoint(0)->setWeapon(new Gun());
    playerShip->components().hardpoint(1)->setWeapon(new Gun());

    playerShip->components().engineSlot(0)->setEngine(new PirateThruster());

    game->player().setShip(playerShip);

    world->god().scheduleSpawn(playerShip);

    ship = worldObjectFactory.build<Ship>("basicship");
    ship->transform().setPosition(glm::vec3(0, 0, 0));
    ship->components().engineSlot(0)->setEngine(new PirateThruster());
    PatrolWaypointsTask* ta = new PatrolWaypointsTask(
        *ship,
        std::list<glm::vec3>{ glm::vec3(0, 0, 0), glm::vec3(-400, 0, 0), glm::vec3(-400, 200, 390) });
    ship->setCharacter(
        new DummyCharacter(*ship, ta)
        );
    world->god().scheduleSpawn(ship);



    glow::debug("Initial spawn");
    world->god().spawn();
}

