#include "voxelexplosioncluster.h"

#include "voxel/specialvoxels/hardpointvoxel.h"
#include "worldobject/weapons/gun.h"
#include "worldobject/weapons/rocketlauncher.h"

VoxelExplosionCluster::VoxelExplosionCluster(float scale, float lifetime) :
    WorldObject(scale, glm::vec3(0, 0, 0), CollisionFilterClass::ExplosionParticle),
    m_lifetime(lifetime)
{
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);
    m_objectInfo.setName("Particle");
    setCollideableWith(CollisionFilterClass::ExplosionParticle, false);
    setCollideableWith(CollisionFilterClass::Bullet, false);
}

void VoxelExplosionCluster::update(float deltasec){
    m_lifetime -= deltasec;
    if (m_lifetime < 0)
        World::instance()->god().scheduleRemoval(this);
}

void VoxelExplosionCluster::onCollision(){
    glow::debug("collision");
    World::instance()->god().scheduleRemoval(this);
}