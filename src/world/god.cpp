
#include "god.h"
#include "collision/collisiondetector.h"
#include "world.h"
#include "worldTree/worldTree.h"
#include "utils/tostring.h"
#include "worldobject.h"


God::God(World & world): 
    m_world(world) 
{
}

God::~God() {

}

void God::scheduleSpawn(WorldObject *cluster) {
    assert(cluster->geode() == nullptr);
    assert(cluster->worldTree() == nullptr);
    m_scheduledSpawns.push_back(cluster);
}

void God::scheduleSpawns(const std::list<WorldObject*> &spawns) {
#ifndef NDEBUG // only spawn things that aren't in a worldTree
    for (PhysicalVoxelCluster* cluster : spawns){
        assert(cluster->geode() == nullptr);
        assert(cluster->worldTree() == nullptr);
    }
#endif
    m_scheduledSpawns.insert(m_scheduledSpawns.end(), spawns.begin(), spawns.end());
}

void God::scheduleRemoval(WorldObject *cluster) {
    assert(cluster->geode() != nullptr);
    assert(cluster->worldTree() == &m_world.worldTree());
    m_scheduledRemovals.push_back(cluster);
}

void God::scheduleRemovals(const std::list<WorldObject*> &removals) {
#ifndef NDEBUG // only remove things that are in our worldTree
    for (WorldObject* cluster : removals) {
        assert(cluster->geode() != nullptr);
        assert(cluster->worldTree() == &m_world.worldTree());
    }
#endif
    m_scheduledRemovals.insert(m_scheduledRemovals.end(), removals.begin(), removals.end());
}

void God::spawn() {
    for (WorldObject* cluster : m_scheduledSpawns) {
        m_world.worldTree().insert(cluster);

        CollisionDetector detector(World::instance()->worldTree(), *cluster);
        std::list<Collision> collisions = detector.checkCollisions();

        assert(collisions.size() == 0); // this is, by definition, an error condition
        if (collisions.size() > 0){ // clean up anyway (if assertion ignored)
            World::instance()->worldTree().remove(cluster->geode());
            glow::warning("Failed to spawn object %; at AABB %;", cluster, toString(cluster->aabb()));
            continue;
        }

        m_world.clusters().push_back(cluster);
    }
    m_scheduledSpawns.clear();
}

void God::remove() {
    for (WorldObject* cluster : m_scheduledRemovals) {
        m_world.worldTree().remove(cluster->geode());
        m_world.clusters().remove(cluster);
        delete cluster;
    }
    m_scheduledRemovals.clear();
}



