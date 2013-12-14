#include "voxelexplosioncluster.h"

#include "voxel/specialvoxels/hardpointvoxel.h"
#include "worldobject/weapons/gun.h"
#include "worldobject/weapons/rocketlauncher.h"

VoxelExplosionCluster::VoxelExplosionCluster(float scale, float lifetime) :
    WorldObject(scale),
    m_lifetime(lifetime)
{
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);
    m_objectInfo.setName("Particle");
}

void VoxelExplosionCluster::update(float deltasec){
    m_lifetime -= deltasec;
    if (m_lifetime < 0)
        World::instance()->god().scheduleRemoval(this);
}

void VoxelExplosionCluster::onCollision(){
    World::instance()->god().scheduleRemoval(this);
}