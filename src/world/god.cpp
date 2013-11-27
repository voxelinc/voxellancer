
#include "god.h"
#include "physicalvoxelcluster.h"
#include "collision/collisiondetector.h"
#include "world.h"
#include "worldtree/worldtree.h"
#include "utils/tostring.h"


God::God(World & world): 
    m_world(world) 
{
}

God::~God() {

}

void God::scheduleSpawn(PhysicalVoxelCluster *cluster) {
    assert(cluster->geode() == nullptr);
    assert(cluster->worldTree() == nullptr);
    m_scheduledSpawns.push_back(cluster);
}

void God::scheduleSpawns(const std::list<PhysicalVoxelCluster*> &spawns) {
#ifndef NDEBUG // only spawn things that aren't in a worldtree
    for (PhysicalVoxelCluster* cluster : spawns){
        assert(cluster->geode() == nullptr);
        assert(cluster->worldTree() == nullptr);
    }
#endif
    m_scheduledSpawns.insert(m_scheduledSpawns.end(), spawns.begin(), spawns.end());
}

void God::scheduleRemoval(PhysicalVoxelCluster *cluster) {
    assert(cluster->geode() != nullptr);
    assert(cluster->worldTree() == &m_world.worldtree());
    m_scheduledRemovals.push_back(cluster);
}

void God::scheduleRemovals(const std::list<PhysicalVoxelCluster*> &removals) {
#ifndef NDEBUG // only remove things that are in our worldtree
    for (PhysicalVoxelCluster* cluster : removals){
        assert(cluster->geode() != nullptr);
        assert(cluster->worldTree() == &m_world.worldtree());
    }
#endif
    m_scheduledRemovals.insert(m_scheduledRemovals.end(), removals.begin(), removals.end());
}

void God::spawn() {
    for (PhysicalVoxelCluster* cluster : m_scheduledSpawns){
        m_world.worldtree().insert(cluster);

        CollisionDetector detector(World::instance()->worldtree(), *cluster);
        std::list<Collision> collisions = detector.checkCollisions();

        assert(collisions.size() == 0); // this is, by definition, an error condition
        if (collisions.size() > 0){ // clean up anyway (if assertion ignored)
            World::instance()->worldtree().remove(cluster->geode());
            glow::warning("Failed to spawn object %; at AABB %;", cluster, toString(cluster->aabb()));
            continue;
        }

        m_world.clusters().push_back(cluster);
    }
    m_scheduledSpawns.clear();
}

void God::remove() {
    for (PhysicalVoxelCluster* cluster : m_scheduledRemovals) {
        m_world.worldtree().remove(cluster->geode());
        m_world.clusters().remove(cluster);
        delete cluster;
    }
    m_scheduledRemovals.clear();
}



