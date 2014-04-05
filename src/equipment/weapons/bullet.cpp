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
}

void Bullet::update(float deltaSec) {
    Projectile::update(deltaSec);
}

bool Bullet::passiveForCollisionDetection() {
    return true;
}

