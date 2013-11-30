
#include "god.h"
#include "collision/collisiondetector.h"
#include "world.h"
#include "worldtree/worldtree.h"
#include "utils/tostring.h"
#include "worldobject.h"


God::God(World & world):
    m_world(world)
{
}

God::~God() {

}

void God::scheduleSpawn(WorldObject *worldObject) {
    assert(worldObject->geode() == nullptr);
    assert(worldObject->worldTree() == nullptr);
    m_scheduledSpawns.push_back(worldObject);
}

void God::scheduleSpawns(const std::list<WorldObject*> &spawns) {
#ifndef NDEBUG // only spawn things that aren't in a worldTree
    for (PhysicalVoxelCluster* worldObject : spawns){
        assert(worldObject->geode() == nullptr);
        assert(worldObject->worldTree() == nullptr);
    }
#endif
    m_scheduledSpawns.insert(m_scheduledSpawns.end(), spawns.begin(), spawns.end());
}

void God::scheduleRemoval(WorldObject *worldObject) {
    assert(worldObject->geode() != nullptr);
    assert(worldObject->worldTree() == &m_world.worldTree());
    m_scheduledRemovals.push_back(worldObject);
}

void God::scheduleRemovals(const std::list<WorldObject*> &removals) {
#ifndef NDEBUG // only remove things that are in our worldTree
    for (WorldObject* worldObject : removals) {
        assert(worldObject->geode() != nullptr);
        assert(worldObject->worldTree() == &m_world.worldTree());
    }
#endif
    m_scheduledRemovals.insert(m_scheduledRemovals.end(), removals.begin(), removals.end());
}

void God::spawn() {
    for (WorldObject* worldObject : m_scheduledSpawns) {
        m_world.worldTree().insert(worldObject);

        std::list<Collision> collisions = worldObject->collisionDetector().checkCollisions();

        assert(collisions.size() == 0); // this is, by definition, an error condition
        if (collisions.size() > 0){ // clean up anyway (if assertion ignored)
            World::instance()->worldTree().remove(worldObject->geode());
            glow::warning("Failed to spawn object %; at AABB %;", worldObject, toString(worldObject->aabb()));
            continue;
        }

        m_world.worldObjects().push_back(worldObject);
    }
    m_scheduledSpawns.clear();
}

void God::remove() {
    for (WorldObject* worldObject : m_scheduledRemovals) {
        m_world.worldTree().remove(worldObject->geode());
        m_world.worldObjects().remove(worldObject);
        delete worldObject;
    }
    m_scheduledRemovals.clear();
}



