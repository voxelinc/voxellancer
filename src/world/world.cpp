#include "world.h"

#include "voxeleffect/particleworld.h"

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
    m_particleWorld = std::unique_ptr<ParticleWorld>(new ParticleWorld());
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

ParticleWorld &World::particleWorld() {
    return *m_particleWorld;
}

std::list<WorldObject*> &World::worldObjects() {
    return m_worldObjects;
}

void World::update(float deltaSecs) {
    m_deltaSec = deltaSecs;

    m_worldLogic->update(deltaSecs);
    m_particleWorld->update(deltaSecs);

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

