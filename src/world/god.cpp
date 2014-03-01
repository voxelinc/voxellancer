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

void God::scheduleSpawn(SpawnRequest spawnRequest) {
    m_spawnRequests.push_back(spawnRequest);
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

void God::spawn() {
    for (SpawnRequest& spawnRequest : m_spawnRequests) {
        for (WorldObject* worldObject : spawnRequest.worldObjects()) {
            m_world.worldTree().insert(worldObject);

            std::list<VoxelCollision> collisions = worldObject->collisionDetector().checkCollisions();

            if (!collisions.empty()){
                World::instance()->worldTree().remove(worldObject->collisionDetector().geode());
                glow::warning("Failed to spawn %;", worldObject->objectInfo().name());
                worldObject->setSpawnState(SpawnState::Rejected);
                worldObject->onSpawnFail();

                if (spawnRequest.deleteOnRejection()) {
                    delete worldObject;
                }
            } else {
                worldObject->setSpawnState(SpawnState::Spawned);
                m_world.addWorldObject(worldObject);
            }
        }
    }
    m_spawnRequests.clear();
}

void God::remove() {
    for (WorldObject* worldObject : m_scheduledRemovals) {
        m_world.worldTree().remove(worldObject->collisionDetector().geode());
        m_world.removeWorldObject(worldObject);
        delete worldObject;
    }
    m_scheduledRemovals.clear();
}



