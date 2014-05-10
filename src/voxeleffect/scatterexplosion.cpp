#include "scatterexplosion.h"

#include <glow/logging.h>

#include "voxelexplosiongenerator.h"


ScatterExplosion::ScatterExplosion(uint32_t color,
                     float force, float forceRandomization,
                     int count, float scale, float emissiveness,
                     float lifetime, float lifetimeRandomization):
    m_color(color),
    m_force(force),
    m_forceRandomization(forceRandomization),
    m_count(count),
    m_scale(scale),
    m_emissiveness(emissiveness),
    m_lifetime(lifetime),
    m_lifetimeRandomization(lifetimeRandomization)
{
}

ScatterExplosion::~ScatterExplosion() = default;

void ScatterExplosion::spawn(const glm::vec3& position) {
    VoxelExplosionGenerator generator(nullptr);

    generator.setPosition(position);
    generator.setRadius(m_scale);
    generator.setScale(m_scale);
    generator.setCount(m_count);
    generator.setEmissiveness(m_emissiveness);
    generator.setColor(m_color);
    generator.setForce(m_force, m_forceRandomization);
    generator.setLifetime(m_lifetime, m_lifetimeRandomization);

    generator.spawn();
}

