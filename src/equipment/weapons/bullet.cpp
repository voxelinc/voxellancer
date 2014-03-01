#include "bullet.h"

#include "collision/collisionfilter.h"

#include "world/god.h"
#include "world/world.h"
#include "ui/objectinfo.h"
#include "physics/physics.h"
#include "sound/soundmanager.h"


Bullet::Bullet():
    Projectile()
{
    collisionFilter().setCollisionFilterClass(CollisionFilterClass::Bullet);
    collisionFilter().setCollideableWith(CollisionFilterClass::Bullet, false);

    m_objectInfo->setShowOnHud(false);
    m_objectInfo->setCanLockOn(false);

    m_physics->setDirectionalDampening(0.0f);
    m_physics->setAngularDampening(0.0f);
}


WorldObjectType Bullet::objectType() const {
    return WorldObjectType::Bullet;
}

void Bullet::update(float deltaSec) {
    Projectile::update(deltaSec);
}

