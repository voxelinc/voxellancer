#pragma once

#include <cmath>

#include <glm/glm.hpp>

#include "worldtransform.h"


class VoxelParticle {
public:
    VoxelParticle(const WorldTransform& transform, int color, float m_lifetime = INFINITY);

    const WorldTransform& worldTransform() const;
    void setWorldTransform(const WorldTransform& transform);

    int color() const;
    const glm::vec3& colorVec() const;

    float lifetime() const;
    bool isDead() const;

    void setDirectionalSpeed(const glm::vec3& speed, float dampening);
    void setAngularSpeed(const glm::vec3& speed, float dampening);

    void update(float deltaSec);


protected:
    WorldTransform m_transform;

    int m_color;
    glm::vec3 m_colorVec;

    float m_lifetime;

    glm::vec3 m_directionalSpeed;
    float m_directionalDampening;

    glm::vec3 m_angularSpeed;
    float m_angularDampening;
};
