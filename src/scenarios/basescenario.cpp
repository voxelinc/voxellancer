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
#include "world/world.h"
#include "world/god.h"

BaseScenario::BaseScenario(Game* game) :
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

void BaseScenario::createPlanet(glm::vec3 position, int diameter, int color) {
    WorldObject *planet = new WorldObject();
    planet->move(position);
    glm::vec3 middle(diameter / 2, diameter / 2, diameter / 2);
    for (int x = 0; x < diameter; x++) {
        for (int y = 0; y < diameter; y++) {
            for (int z = 0; z < diameter; z++) {
                glm::vec3 cell(x, y, z);

                if (glm::length(cell - middle) < diameter / 2) {
                    planet->addVoxel(new Voxel(glm::ivec3(x, y, z), color));
                }
            }
        }
    }
    planet->setCrucialVoxel(glm::ivec3(middle));
    planet->objectInfo().setName("Planet");
    planet->objectInfo().setShowOnHud(true);
    planet->objectInfo().setCanLockOn(true);
    m_world->god().scheduleSpawn(planet);
}

void BaseScenario::onKeyPressed(int key) {

}