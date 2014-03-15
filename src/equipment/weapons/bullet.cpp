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
    collisionFilter().setCollideableWith(WorldObjectType::Bullet, false);

    m_objectInfo->setShowOnHud(false);
    m_objectInfo->setCanLockOn(false);

    m_physics->setDirectionalDampening(unnamed_property(0.0f));
    m_physics->setAngularDampening(unnamed_property(0.0f));
}


WorldObjectType Bullet::objectType() const {
    return WorldObjectType::Bullet;
}

void Bullet::update(float deltaSec) {
    Projectile::update(deltaSec);
}

