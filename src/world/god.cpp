#include "god.h"

#include <glow/logging.h>

#include "collision/collisiondetector.h"

#include "scripting/scriptengine.h"

#include "ui/objectinfo.h"

#include "worldtree/worldtree.h"

#include "worldobject/worldobject.h"

#include "world.h"


God::God(World& world):
    m_world(world)
{
}

God::~God() {

}

void God::scheduleSpawn(WorldObject* worldObject) {
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

const std::list<WorldObject*>& God::scheduledSpawns(){
    return m_scheduledSpawns;
}

void God::scheduleRemoval(WorldObject* worldObject) {
    assert(worldObject->collisionDetector().geode() != nullptr);
    assert(worldObject->collisionDetector().worldTree() == &m_world.worldTree());
    for (WorldObject* scheduled : m_scheduledRemovals){
        if (scheduled == worldObject) {
            return;
        }
    }
    m_scheduledRemovals.push_back(worldObject);
    worldObject->onScheduleForDeletion();
}

void God::scheduleRemovals(const std::list<WorldObject*> &removals) {
    for (WorldObject* worldObject : removals) {
        scheduleRemoval(worldObject);
    }
}

const std::list<WorldObject*>& God::scheduledRemovals(){
    return m_scheduledRemovals;
}

void God::spawn() {
    for (WorldObject* worldObject : m_scheduledSpawns) {
        m_world.worldTree().insert(worldObject);

        std::list<VoxelCollision> collisions = worldObject->collisionDetector().checkCollisions();

        if (!collisions.empty()){
            World::instance()->worldTree().remove(worldObject->collisionDetector().geode());
            glow::warning("Failed to spawn %;", worldObject->objectInfo().name());
            worldObject->onSpawnFail();
            delete worldObject;
            continue;
        }

        m_world.addWorldObject(worldObject);
    }
    m_scheduledSpawns.clear();
}

void God::remove() {
    for (WorldObject* worldObject : m_scheduledRemovals) {
        m_world.worldTree().remove(worldObject->collisionDetector().geode());
        m_world.removeWorldObject(worldObject);
        delete worldObject;
    }
    m_scheduledRemovals.clear();
}



