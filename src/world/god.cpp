
#include "god.h"
#include "collision/collisiondetector.h"
#include "world.h"
#include "worldtree/worldtree.h"
#include "utils/tostring.h"

#include "worldobject/worldobject.h"



God::God(World & world):
    m_world(world)
{
}

God::~God() {

}

void God::scheduleSpawn(WorldObject *worldObject) {
    assert(worldObject->collisionDetector().geode() == nullptr);
    assert(worldObject->collisionDetector().worldTree() == nullptr);
    m_scheduledSpawns.push_back(worldObject);
}

void God::scheduleSpawns(const std::list<WorldObject*> &spawns) {
#ifndef NDEBUG // only spawn things that aren't in a worldTree
    for (WorldObject* worldObject : spawns){
        assert(worldObject->collisionDetector().geode() == nullptr);
        assert(worldObject->collisionDetector().worldTree() == nullptr);
    }
#endif
    m_scheduledSpawns.insert(m_scheduledSpawns.end(), spawns.begin(), spawns.end());
}

void God::scheduleRemoval(WorldObject *worldObject) {
    assert(worldObject->collisionDetector().geode() != nullptr);
    assert(worldObject->collisionDetector().worldTree() == &m_world.worldTree());
    for (WorldObject* scheduled : m_scheduledRemovals){
        if (scheduled == worldObject)
            return;
    }
    m_scheduledRemovals.push_back(worldObject);
}

void God::scheduleRemovals(const std::list<WorldObject*> &removals) {
    for (WorldObject* worldObject : removals) {
        scheduleRemoval(worldObject);
    }
}

void God::spawn() {
    for (WorldObject* worldObject : m_scheduledSpawns) {
        m_world.worldTree().insert(worldObject);

        std::list<VoxelCollision> collisions = worldObject->collisionDetector().checkCollisions();

        //assert(collisions.size() == 0); // this is, by definition, an error condition
        if (collisions.size() > 0){ // clean up anyway (if assertion ignored)
            World::instance()->worldTree().remove(worldObject->collisionDetector().geode());
            glow::warning("Failed to spawn object %; at AABB %;", worldObject, toString(worldObject->aabb()));
            continue;
        }

        m_world.worldObjects().push_back(worldObject);
    }
    m_scheduledSpawns.clear();
}

void God::remove() {
    for (WorldObject* worldObject : m_scheduledRemovals) {
        m_world.worldTree().remove(worldObject->collisionDetector().geode());
        m_world.worldObjects().remove(worldObject);
        delete worldObject;
    }
    m_scheduledRemovals.clear();
}



