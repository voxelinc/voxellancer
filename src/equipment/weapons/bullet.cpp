#include "bullet.h"

#include "collision/collisionfilter.h"

#include "physics/physics.h"

#include "sound/soundmanager.h"

#include "voxeleffect/explosion.h"

#include "world/god.h"
#include "world/world.h"


Bullet::Bullet() {
    collisionFilter().setCollideableWith(WorldObjectType::Bullet, false);

    m_physics->setDirectionalDampening(unnamedProperty(0.0f));
    m_physics->setAngularDampening(unnamedProperty(0.0f));
}

WorldObjectType Bullet::objectType() const {
    return WorldObjectType::Bullet;
}

void Bullet::update(float deltaSec) {
    Projectile::update(deltaSec);
}

bool Bullet::passiveForCollisionDetection() {
    return true;
}

