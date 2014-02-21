#include "genericrocket.h"

#include "property/property.h"

#include "voxeleffect/voxelexplosiongenerator.h"
#include "sound/soundmanager.h"


GenericRocket::GenericRocket()
{
}

void GenericRocket::onLifetimeOver() {
    spawnExplosion();
}

void GenericRocket::spawnExplosion() {
    VoxelExplosionGenerator generator;

    generator.setPosition(m_transform.position());
    generator.setScale(m_transform.scale() / 3.0f);
    generator.setColor(0xFF0000);
    generator.setEmissiveness(0.4f);
    generator.setCount(150);
    generator.setLifetime(1.0f, 0.2f);
    generator.setForce(1.5f);

    generator.spawn();
}
