#include "mover.h"
#include "../god.h"
#include "../world.h"
#include "worldobject/worldobject.h"


void Mover::moveVoxelClusters(float delta_sec) {
    m_collisions.clear();

    for (WorldObject *cluster : World::instance()->clusters()) {
        std::list<Collision> &collisions = cluster->move(delta_sec);
        m_collisions.insert(m_collisions.end(), collisions.begin(), collisions.end());
    }
}

const std::list<Collision> &Mover::collisions() {
    return m_collisions;
}
