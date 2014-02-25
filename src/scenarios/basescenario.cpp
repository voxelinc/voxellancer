#include "basescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>
#include <glowutils/Timer.h>

#include "ai/character.h"

#include "resource/clustercache.h"

#include "resource/worldobjectbuilder.h"
#include "worldobject/ship.h"
#include "ui/objectinfo.h"
#include "sound/soundmanager.h"
#include "world/world.h"
#include "world/god.h"
#include "game.h"
#include "player.h"


BaseScenario::BaseScenario(Game* game):
    m_game(game)
{
}

void BaseScenario::load() {
    {
        glowutils::AutoTimer timer("Creating World took");
        createWorld();
    }
    {
        glowutils::AutoTimer timer("Populating World took");
        populateWorld();
    }
}

void BaseScenario::clear() {
    m_world->reset();
}


void BaseScenario::reset() {
    clear();
    load();
}

void BaseScenario::createWorld() {
    m_world = World::instance();
}

void BaseScenario::populateWorld() {
    // Any scenario must set the player ship atm
    Ship *playerShip = WorldObjectBuilder("basicship").buildShip();
    playerShip->transform().setPosition(glm::vec3(0, 0, 10));
    playerShip->objectInfo().setName("basicship");
    playerShip->objectInfo().setShowOnHud(false);
    playerShip->objectInfo().setCanLockOn(false);
    m_world->god().scheduleSpawn(playerShip);
    m_game->player().setShip(playerShip);
    m_world->god().spawn();
}
