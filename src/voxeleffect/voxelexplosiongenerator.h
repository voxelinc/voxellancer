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
    void setScale(float scale);
    void setTransform(const WorldTransform& transform);
    void setForce(float force);
    void setColor(int color);
    void setDensity(int density);
    void setImpactVector(const glm::vec3& impactVector);

    void spawn();

protected:
    Property<float> prop_lifetime;
    glm::vec3 m_position;
    glm::quat m_orientation;
    float m_scale;
    float m_force;
    int m_color;
    int m_density;
    glm::vec3 m_impactVector;

};

