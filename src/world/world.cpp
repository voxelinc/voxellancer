#include "world.h"

#include "voxeleffect/voxelparticleengine.h"

#include "worldtree/worldtree.h"
#include "worldlogic.h"
#include "worldobject/worldobject.h"
#include "skybox.h"
#include "scripting/scriptengine.h"

#include "god.h"


World *World::s_instance = nullptr;

World::World():
    m_skybox(new Skybox()),
    m_worldLogic(new WorldLogic(*this)),
    m_worldTree(new WorldTree()),
    m_god(new God(*this)),
    m_voxelParticleEngine(new VoxelParticleEngine()),
    m_scriptEngine(new ScriptEngine(this))
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

VoxelParticleEngine &World::voxelParticleEngine() {
    return *m_voxelParticleEngine;
}

ScriptEngine& World::scriptEngine() {
    return *m_scriptEngine;
}

std::unordered_set<WorldObject*> &World::worldObjects() {
    return m_worldObjects;
}

void World::update(float deltaSecs) {
    m_deltaSec = deltaSecs;

    m_worldLogic->update(deltaSecs);
    m_voxelParticleEngine->update(deltaSecs);
    m_scriptEngine->update(deltaSecs);

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
    s_instance = nullptr;
}

