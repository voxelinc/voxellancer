#include "world.h"

#include "events/eventpoller.h"

#include "factions/factionmatrix.h"

#include "voxeleffect/voxelparticleengine.h"

#include "worldtree/worldtree.h"

#include "worldobject/ship.h"
#include "worldobject/worldobject.h"

#include "skybox.h"
#include "scripting/scriptengine.h"

#include "worldlogic.h"
#include "god.h"


World *World::s_instance = nullptr;

World::World():
    m_skybox(new Skybox()),
    m_worldLogic(new WorldLogic(*this)),
    m_worldTree(new WorldTree()),
    m_god(new God(*this)),
    m_scriptEngine(new ScriptEngine(this)),
    m_particleEngine(new VoxelParticleEngine()),
    m_factionMatrix(new FactionMatrix()),
    m_eventPoller(new EventPoller())
{
}

World::~World() {

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

    m_worldLogic->update(deltaSecs);
    m_scriptEngine->update(deltaSecs);
    m_eventPoller->update(deltaSecs);
    m_particleEngine->update(deltaSecs);

    for (WorldObject *worldObject : m_worldObjects) {
        worldObject->update(deltaSecs);
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

void World::reset() {
    glow::warning("world reset!");
    delete s_instance;
    s_instance = nullptr;
}

void World::addWorldObject(WorldObject* worldObject) {
    m_worldObjects.insert(worldObject);

    switch(worldObject->objectType()) {
        case WorldObjectType::Ship:
            m_ships.insert(static_cast<Ship*>(worldObject));
        break;
    }

    m_scriptEngine->registerScriptable(worldObject);
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

