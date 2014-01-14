#include "world.h"

#include "voxeleffect/voxelparticleworld.h"

#include "worldtree/worldtree.h"
#include "worldlogic.h"
#include "worldobject/worldobject.h"

#include "god.h"


World *World::s_instance = nullptr;

World::World()
{
    m_worldLogic = std::unique_ptr<WorldLogic>(new WorldLogic(*this));
    m_worldTree = std::unique_ptr<WorldTree>(new WorldTree());
    m_god = std::unique_ptr<God>(new God(*this));
    m_voxelParticleWorld = std::unique_ptr<VoxelParticleWorld>(new VoxelParticleWorld());
}

World::~World() {

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

    for (WorldObject *worldObject : m_worldObjects) {
        worldObject->update(deltaSecs);
    }

    m_worldLogic->update(deltaSecs);
    m_voxelParticleWorld->update(deltaSecs);
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

