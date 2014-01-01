#include "voxelexplosionparticle.h"

#include "voxel/specialvoxels/hardpointvoxel.h"
#include "worldobject/weapons/gun.h"
#include "worldobject/weapons/rocketlauncher.h"

VoxelExplosionParticle::VoxelExplosionParticle(float scale, float lifetime) :
    WorldObject(
        new Physics(*this, 
            scale, 
            Property<float>("physics.particleDampening"), 
            Property<float>("physics.particleAngularDampening")), 
        new CollisionDetector(*this), 
        scale, 
        CollisionFilterClass::ExplosionParticle),
    m_lifetime(lifetime)
{
    m_objectInfo.setShowOnHud(false);
    m_objectInfo.setCanLockOn(false);
    m_objectInfo.setName("Particle");
    setCollideableWith(CollisionFilterClass::ExplosionParticle, false);
    setCollideableWith(CollisionFilterClass::Bullet, false);
}

void VoxelExplosionParticle::update(float deltasec){
    m_lifetime -= deltasec;
    if (m_lifetime < 0)
        World::instance()->god().scheduleRemoval(this);
}

void VoxelExplosionParticle::onCollision(){
    World::instance()->god().scheduleRemoval(this);
}