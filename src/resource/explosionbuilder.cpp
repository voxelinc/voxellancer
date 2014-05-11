#include "explosionbuilder.h"

#include "property/property.h"

#include "voxeleffect/noexplosion.h"
#include "voxeleffect/dummyexplosion.h"
#include "voxeleffect/ringexplosion.h"
#include "voxeleffect/scatterexplosion.h"


ExplosionBuilder::ExplosionBuilder(const std::string& prefix):
    m_prefix(prefix)
{
}

std::shared_ptr<Explosion> ExplosionBuilder::build() {
    std::string type = Property<std::string>::get(m_prefix + ".type", "dummy");

    if (type == "scatter") {
        return buildScatterExplosion();
    } else if (type == "dummy") {
        return std::make_shared<DummyExplosion>();
    } else if (type == "ring") {
        return std::make_shared<RingExplosion>();
    } else if (type == "none") {
        return std::make_shared<NoExplosion>();
    } else {
        throw std::runtime_error("No such explosion of type '" + type + "'");
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

std::shared_ptr<Explosion> ExplosionBuilder::buildRingExplosion() {
    auto explosion = std::make_shared<RingExplosion>();

    return explosion;
}


