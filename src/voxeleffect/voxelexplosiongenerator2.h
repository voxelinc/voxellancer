#pragma once
#include <glm/glm.hpp>

#include "property/property.h"

class WorldTransform;

class VoxelExplosionGenerator2
{
public:
    VoxelExplosionGenerator2();
    virtual ~VoxelExplosionGenerator2();

    void setPosition(const glm::vec3& position);
    void setRadius(float radius);
    void setScale(float scale);
    void setForce(float force);
    void setLifetime(float lifetime, float randomization = 0.0f);
    void setColor(int color);
    void setCount(int count);
    void setImpactVector(const glm::vec3& impactVector);

    void spawn();

protected:
    glm::vec3 m_position;
    float m_radius;
    float m_scale;
    float m_force;
    float m_lifetime;
    float m_lifetimeRandomization;
    int m_color;
    int m_count;
    glm::vec3 m_impactVector;

};
