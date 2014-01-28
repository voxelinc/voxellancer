#include "basescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>
#include <glowutils/Timer.h>

#include "ai/characters/dummycharacter.h"
#include "ai/elevatedtasks/dummyelevatedtask.h"
#include "ai/basictask.h"

#include "resource/clustercache.h"

#include "worldobject/ship.h"
#include "sound/soundmanager.h"

BaseScenario::BaseScenario(Game* game) :
m_game(game)
{
}

void BaseScenario::clear() {
    m_world->reset();
}

void BaseScenario::load() {
    glowutils::Timer timer("Create Scenario");
    glow::debug("Create World");
    timer.start();
    m_world = World::instance();
    glow::debug("Creating World took %;", timer.elapsed());
    timer.reset();
    glow::debug("Populate World");
    timer.start();
    populateWorld();
    glow::debug("Populating World took %;", timer.elapsed());
}

void BaseScenario::reset() {
    clear();
    load();
}

void BaseScenario::createWorld() {
    m_world = World::instance();
    SoundManager::current();
}

void BaseScenario::populateWorld() {

}