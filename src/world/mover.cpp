#include "mover.h"


void Mover::moveVoxelClusters() {
    m_collisions.clear();
    /**
        TODO: Grab all voxelclusters from world->god and move them
        The move() method of the voxelcluster should return the occured collisions
        and Mover should store them in m_collisions;
    **/
}

const std::list<Collision> &Mover::collisions() {
    return m_collisions;
}
