
#include <glow/logging.h>

#include "god.h"
#include "collision/collisiondetector.h"
#include "world.h"
#include "worldtree/worldtree.h"
#include "utils/tostring.h"

#include "worldobject/worldobject.h"
#include "ui/objectinfo.h"



God::God(World& world):
    m_world(world)
{
}

God::~God() {

}

void God::scheduleSpawn(WorldObject* worldObject) {
    assert(worldObject->collisionDetector().geode() == nullptr);
    assert(worldObject->collisionDetector().worldTree() == nullptr);
    worldObject->setSpawnState(SpawnState::SpawnScheduled);
    m_scheduledSpawns.push_back(worldObject);
}

void God::scheduleSpawns(const std::list<WorldObject*> &spawns) {
    for (WorldObject* worldObject : spawns){
        scheduleSpawn(worldObject);
    }
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
    worldObject->setSpawnState(SpawnState::RemovalScheduled);
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
            worldObject->setSpawnState(SpawnState::Rejected);
            worldObject->onSpawnFail();
        } else {
            worldObject->setSpawnState(SpawnState::Spawned);
            m_world.addWorldObject(worldObject);
        }
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



