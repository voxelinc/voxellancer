#pragma once

#include <glm/glm.hpp>

#include "property/property.h"

class Transform;

class VoxelParticleSpawnBase
{
public:
    VoxelParticleSpawnBase();
    virtual ~VoxelParticleSpawnBase();

    void setPosition(const glm::vec3& position);
    void setOrientation(const glm::quat& orientation);
    void setScale(float scale, float randomization = 0.0f);
    void setForce(float force, float randomization = 0.0f);
    void setLifetime(float lifetime, float randomization = 0.0f);
    void setColor(int color, float emissiveness = 0.0f);
    void setImpactVector(const glm::vec3& impactVector);


protected:
    glm::vec3 m_position;
    float m_scale;
    float m_scaleRandomization;
    float m_force;
    float m_forceRandomization;
    float m_lifetime;
    float m_lifetimeRandomization;
    int m_color;
    float m_colorEmissiveness;
    glm::vec3 m_impactVector;

    float m_particleDampening;
    float m_particleAngularDampening;
    float m_particleBaseForce;
    float m_particleAngularBaseForce;


    glm::vec3 createDirectionalSpeed();
    glm::vec3 createAngularSpeed();
    float createLifetime();
};

