#pragma once

#include <cstdint>

#include "explosion.h"


class ScatterExplosion : public Explosion {
public:
    ScatterExplosion(uint32_t color,
                     float force, float forceRandomization,
                     int count, float scale, float emissiveness,
                     float lifetime, float lifetimeRandomization);
    virtual ~ScatterExplosion() override;

    virtual void spawn(const glm::vec3& position) override;

protected:
    uint32_t m_color;
    float m_force;
    float m_forceRandomization;
    int m_count;
    float m_scale;
    float m_emissiveness;
    float m_lifetime;
    float m_lifetimeRandomization;
};

