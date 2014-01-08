#pragma once

#include <glm/glm.hpp>

#include "property/property.h"

class WorldTransform;

class VoxelExplosionGenerator
{
public:
    VoxelExplosionGenerator();
    virtual ~VoxelExplosionGenerator();

    void setPosition(const glm::vec3& position);
    void setOrientation(const glm::quat& orientation);
    void setScale(float scale, float randomization = 0.0f);
    void setTransform(const WorldTransform& transform);
    void setForce(float force, float randomization = 0.0f);
    void setLifetime(float lifetime, float randomization = 0.0f);
    void setColor(int color);
    void setDensity(int density);
    void setImpactVector(const glm::vec3& impactVector);

    void spawn();

protected:
    glm::vec3 m_position;
    glm::quat m_orientation;
    float m_scale;
    float m_scaleRandomization;
    float m_force;
    float m_forceRandomization;
    float m_lifetime;
    float m_lifetimeRandomization;
    int m_color;
    int m_density;
    glm::vec3 m_impactVector;


    glm::vec3 createDirectionalSpeed() const;
    glm::vec3 createAngularSpeed() const;
    float createLifetime() const;
    float createScale() const;
};

