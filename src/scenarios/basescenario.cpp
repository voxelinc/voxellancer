#include "basescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>
#include <glowutils/Timer.h>

#include "ai/character.h"

#include "resource/clustercache.h"

#include "worldobject/ship.h"
#include "sound/soundmanager.h"
#include "world/world.h"


BaseScenario::BaseScenario(Game* game):
    m_game(game)
{
}

void BaseScenario::clear() {
    m_world->reset();
}

void BaseScenario::load() {
    {
        glowutils::AutoTimer timer("Creating World took");
        m_world = World::instance();
    }
    {
        glowutils::AutoTimer timer("Populating World took");
        populateWorld();
    }
}

void BaseScenario::reset() {
    clear();
    load();
}

void BaseScenario::createWorld() {
    m_world = World::instance();
}

void BaseScenario::populateWorld() {

}
