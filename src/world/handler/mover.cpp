#include "mover.h"
#include "../god.h"
#include "../world.h"
#include "../worldobject.h"


void Mover::moveVoxelClusters(float delta_sec) {
    m_collisions.clear();
    /**
        TODO: Grab all voxelclusters from world->god and move them
        The move() method of the voxelcluster should return the occured collisions
        and Mover should store them in m_collisions;
    **/

    for (WorldObject *cluster : World::instance()->clusters()) {
        std::list<Collision> &collisions = cluster->move(delta_sec);
        m_collisions.insert(m_collisions.end(), collisions.begin(), collisions.end());
    }
}

const std::list<Collision> &Mover::collisions() {
    return m_collisions;
}
