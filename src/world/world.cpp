#include "world.h"

#include "events/eventpoller.h"

#include "factions/factionmatrix.h"

#include "voxeleffect/voxelparticleengine.h"

#include "worldtree/worldtree.h"

#include "worldobject/ship.h"
#include "worldobject/worldobject.h"

#include "display/rendering/skybox.h"
#include "scripting/scriptengine.h"

#include "worldlogic.h"
#include "god.h"
#include "player.h"
#include "worldelement.h"


World *World::s_instance = nullptr;

World::World():
    m_player(new Player()),
    m_scriptEngine(new ScriptEngine()),
    m_skybox(new Skybox()),
    m_worldLogic(new WorldLogic(*this)),
    m_worldTree(new WorldTree()),
    m_god(new God(*this)),
    m_particleEngine(new VoxelParticleEngine()),
    m_factionMatrix(new FactionMatrix()),
    m_eventPoller(new EventPoller())
{
}

World::~World() {

}

Player& World::player() {
    return *m_player;
}

Skybox &World::skybox() {
    return *m_skybox;
}

WorldLogic &World::worldLogic() {
    return *m_worldLogic;
}

God &World::god() {
    return *m_god;
}

WorldTree &World::worldTree() {
    return *m_worldTree;
}

VoxelParticleEngine &World::particleEngine() {
    return *m_particleEngine;
}

ScriptEngine& World::scriptEngine() {
    return *m_scriptEngine;
}

FactionMatrix &World::factionMatrix() {
    return *m_factionMatrix;
}

EventPoller &World::eventPoller() {
    return *m_eventPoller;
}

std::unordered_set<WorldObject*> &World::worldObjects() {
    return m_worldObjects;
}

std::unordered_set<Ship*> &World::ships() {
    return m_ships;
}

void World::update(float deltaSecs) {
    m_deltaSec = deltaSecs;

    m_player->update(deltaSecs);
    m_worldLogic->update(deltaSecs);
    m_scriptEngine->update(deltaSecs);
    m_eventPoller->update(deltaSecs);
    m_particleEngine->update(deltaSecs);

    for (WorldObject *worldObject : m_worldObjects) {
        worldObject->update(deltaSecs);
    }

    for (auto iter = m_elements.begin(); iter != m_elements.end(); ) {
        WorldElement* element = *iter;

        element->update(deltaSecs);

        if (m_scheduledRemovals.find(element) != m_scheduledRemovals.end()) {
            element->onRemovalFromWorld();
            m_scriptEngine->unregisterScriptable(element);
            element->setWorld(nullptr);

            iter = m_elements.erase(iter);
        } else {
            ++iter;
        }
    }
}

float World::deltaSec() const {
    return m_deltaSec;
}

World *World::instance() {
    if(s_instance == nullptr) {
        s_instance = new World();
    }

    return s_instance;
}

void World::reset(bool showWarning) {
    if (showWarning) {
        glow::warning("world reset!");
    }
    delete s_instance;
    s_instance = nullptr;
}

void World::addElement(WorldElement* element) {
    if (!element->isAddableToWorld(this)) {
        glow::warning("World: Couldn't add WorldElement");
        return;
    }

    m_elements.push_back(element);
    m_scriptEngine->registerScriptable(element);

    element->setWorld(this);
    element->onAddToWorld();
}

void  World::removeElement(WorldElement* element) {
    m_scheduledRemovals.insert(element);
}

void World::addWorldObject(WorldObject* worldObject) {
    m_worldObjects.insert(worldObject);

    switch(worldObject->objectType()) {
        case WorldObjectType::Ship:
            m_ships.insert(static_cast<Ship*>(worldObject));
            m_scriptEngine->registerScriptable(worldObject);
        break;
    }
}

void World::removeWorldObject(WorldObject* worldObject) {
    m_worldObjects.erase(worldObject);

    switch(worldObject->objectType()) {
        case WorldObjectType::Ship:
            m_ships.erase(static_cast<Ship*>(worldObject));
        break;
    }

    m_scriptEngine->unregisterScriptable(worldObject);
}

void World::printStatus() {
    int worldObjectCount = m_worldObjects.size();
    int voxelCount = 0;
    for (WorldObject* worldObject : m_worldObjects) {
        voxelCount += worldObject->voxelMap().size();
    }
    int particleCount = m_particleEngine->particleCount();

    glow::info("World: status report");
    glow::info("  Worldobjects: %;", worldObjectCount);
    glow::info("  VoxelCount: %;", voxelCount);
    glow::info("  ParticleCount: %;", particleCount);
}


