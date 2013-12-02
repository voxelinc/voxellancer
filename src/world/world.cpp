#include "world.h"

#include "god.h"
#include "worldtree/worldtree.h"
#include "worldlogic.h"
#include "worldobject/worldobject.h"

World *World::s_instance = nullptr;

World::World()
{
    m_worldLogic = std::unique_ptr<WorldLogic>(new WorldLogic(*this));
    m_worldTree = std::unique_ptr<WorldTree>(new WorldTree());
    m_god = std::unique_ptr<God>(new God(*this));
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

std::list<WorldObject*> &World::worldObjects() {
    return m_worldObjects;
}

void World::update(float deltaSecs) {
    // move to a game mechanic specific class?
    for (WorldObject *cluster : m_clusters) {
        cluster->update(deltaSecs);
    }
    m_deltaSecs = deltaSecs;

    m_worldLogic->update(deltaSecs);
}

World *World::instance() {
    if(s_instance == nullptr) {
        s_instance = new World();
    }

    return s_instance;
}

