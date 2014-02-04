#include "genericbullet.h"

#include <iostream>

#include "voxeleffect/voxelexplosiongenerator.h"


GenericBullet::GenericBullet(const std::string& propertyPrefix):
    GenericWorldObject(propertyPrefix)
{
    setLifetime(Property<float>(propertyPrefix + ".general.lifetime"));
}

void GenericBullet::spawnExplosion() {
    VoxelExplosionGenerator generator;

    generator.setPosition(m_transform.position());
    generator.setRadius(m_transform.scale());
    generator.setScale(m_transform.scale() / 2.0f);
    generator.setCount(16);
    generator.setColor(0xFF0000);
    generator.setForce(0.6f);
    generator.setLifetime(0.7f, 0.2f);

    generator.spawn();
}

