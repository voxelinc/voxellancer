#pragma once

#include <glm/glm.hpp>

#include "property/property.h"

class Transform;

class VoxelParticleSpawnBase {
public:
    VoxelParticleSpawnBase();

    void setPosition(const glm::vec3& position);
    void setOrientation(const glm::quat& orientation);
    void setScale(float scale, float randomization = 0.0f);
    void setForce(float force, float randomization = 0.0f);
    void setLifetime(float lifetime, float randomization = 0.0f);
    void setColor(int color);
    void setEmissiveness(float emissiveness);
    void setImpactVector(const glm::vec3& impactVector);


protected:
    VoxelParticleSpawnBase(char* dampeningName,
                           char* angularDampeningName,
                           char* baseForceName,
                           char* angularBaseForceName);

    glm::vec3 m_position;

    float m_scale;
    float m_scaleRandomization;

    float m_force;
    float m_forceRandomization;

    float m_lifetime;
    float m_lifetimeRandomization;

    int m_color;
    float m_emissiveness;

    glm::vec3 m_impactVector;

    Property<float> m_particleDampening;
    Property<float> m_particleAngularDampening;
    Property<float> m_particleBaseForce;
    Property<float> m_particleAngularBaseForce;


    glm::vec3 createDirectionalSpeed();
    glm::vec3 createAngularSpeed();
    float createLifetime();
};

