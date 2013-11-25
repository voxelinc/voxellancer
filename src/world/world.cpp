#include "world.h"

#include "voxel/voxel.h"


World *World::s_instance = nullptr;

World::World()
{

}

World::~World() {

}

WorldLogic &World::worldLogic() {
    return m_worldLogic;
}

God &World::god() {
    return m_god;
}

Worldtree &World::worldtree() {
    return m_worldtree;
}

float World::deltaSecs() const {
    return m_deltaSecs;
}

void World::update(float deltaSecs) {
    m_deltaSecs = deltaSecs;
    m_worldLogic.update();
}

World *World::instance() {
    if(s_instance == nullptr) {
        s_instance = new World();
    }

    return s_instance;
}

