#include "bullet.h"

#include "collision/collisionfilter.h"

#include "world/god.h"
#include "world/world.h"
#include "worldobject/worldobjectinfo.h"
#include "physics/physics.h"
#include "sound/soundmanager.h"


Bullet::Bullet()
{
}

void Bullet::update(float deltaSec) {
    Projectile::update(deltaSec);
}

