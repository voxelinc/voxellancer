
#include "god.h"
#include "physicalvoxelcluster.h"
#include "world.h"
#include "worldtree/worldtree.h"


God::God(World & world): 
    m_world(world) 
{
}

God::~God() {

}

std::list<PhysicalVoxelCluster*> &God::voxelClusters() {
	return m_voxelClusters;
}

void God::scheduleSpawn(PhysicalVoxelCluster * cluster) {
    m_scheduledSpawns.push_back(cluster);
}

void God::scheduleSpawns(const std::list<PhysicalVoxelCluster*> &spawns) {
    m_scheduledSpawns.insert(m_scheduledSpawns.end(), spawns.begin(), spawns.end());
}

void God::scheduleRemovals(const std::list<PhysicalVoxelCluster*> &removals) {
    m_scheduledRemovals.insert(m_scheduledRemovals.end(), removals.begin(), removals.end());

}

void God::spawn() {
    m_voxelClusters.insert(m_voxelClusters.end(), m_scheduledSpawns.begin(), m_scheduledSpawns.end());
    for (PhysicalVoxelCluster* cluster : m_scheduledSpawns) {
        m_world.worldtree().insert(cluster);
    }
    m_scheduledSpawns.clear();
}

void God::remove() {
    for (PhysicalVoxelCluster* cluster : m_scheduledRemovals) {
        m_voxelClusters.remove(cluster);
        //m_world.worldtree().remove(cluster->geode()); TODO not implemented yet!!
        // TODO delete cluster??
    }
    m_scheduledRemovals.clear();
}



