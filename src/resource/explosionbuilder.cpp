#include "explosionbuilder.h"

#include "property/property.h"

#include "voxeleffect/noexplosion.h"
#include "voxeleffect/scatterexplosion.h"


ExplosionBuilder::ExplosionBuilder(const std::string& prefix):
    m_prefix(prefix)
{
}

std::shared_ptr<Explosion> ExplosionBuilder::build() {
    std::string name = Property<std::string>::get(m_prefix + ".type", "none");

    if (name == "scatter") {
        return buildScatterExplosion();
    } else if (name == "none") {
        return std::make_shared<NoExplosion>();
    } else {
        throw std::runtime_error("No such explosion named '" + name + "'");
    }
}

std::shared_ptr<Explosion> ExplosionBuilder::buildScatterExplosion() {
    auto explosion = std::make_shared<ScatterExplosion>(
        Property<uint32_t>::get(m_prefix + ".color"),
        Property<float>::get(m_prefix + ".force"),
        Property<float>::get(m_prefix + ".forceRandomization", 0.0f),
        Property<int>::get(m_prefix + ".count"),
        Property<float>::get(m_prefix + ".scale"),
        Property<float>::get(m_prefix + ".emissiveness"),
        Property<float>::get(m_prefix + ".lifetime"),
        Property<float>::get(m_prefix + ".lifetimeRandomization")
    );

    return explosion;
}

