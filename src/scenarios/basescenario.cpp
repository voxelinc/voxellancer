#include "basescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>
#include <glowutils/Timer.h>

#include "ai/character.h"

#include "gamestate/gameplay/gameplay.h"

#include "resource/clustercache.h"

#include "resource/worldelementbuilder.h"
#include "worldobject/ship.h"
#include "scripting/scriptengine.h"
#include "worldobject/worldobjectinfo.h"
#include "sound/soundmanager.h"
#include "world/god.h"
#include "world/world.h"
#include "world/god.h"
#include "player.h"


BaseScenario::BaseScenario(GamePlay* gamePlay) :
    m_gamePlay(gamePlay),
    m_world(nullptr)
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
        m_world->god().spawn();
        m_world->scriptEngine().start();
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

}


