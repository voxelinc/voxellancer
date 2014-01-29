#include "world.h"

#include "voxeleffect/voxelparticleworld.h"

#include "worldtree/worldtree.h"
#include "worldlogic.h"
#include "worldobject/worldobject.h"
#include "skybox.h"

#include "god.h"


World *World::s_instance = nullptr;

World::World():
    m_skybox(new Skybox()),
    m_worldLogic(new WorldLogic(*this)),
    m_worldTree(new WorldTree()),
    m_god(new God(*this)),
    m_voxelParticleWorld(new VoxelParticleWorld()) 
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

VoxelParticleWorld &World::voxelParticleWorld() {
    return *m_voxelParticleWorld;
}

std::list<WorldObject*> &World::worldObjects() {
    return m_worldObjects;
}

void World::update(float deltaSecs) {
    m_deltaSec = deltaSecs;

    m_worldLogic->update(deltaSecs);
    m_voxelParticleWorld->update(deltaSecs);

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

