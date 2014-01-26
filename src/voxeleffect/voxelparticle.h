#pragma once

#include <memory>
#include <cmath>

#include <glm/glm.hpp>

#include "property/property.h"

#include "worldtransform.h"


class VoxelParticle {
public:
    VoxelParticle(const WorldTransform& transform, int color, float emissiveness, float m_lifetime = INFINITY);

    const WorldTransform& worldTransform() const;
    void setWorldTransform(const WorldTransform& transform);

    int color() const;
    float emissiveness() const;

    float lifetime() const;
    bool isDead() const;

    void setDirectionalSpeed(const glm::vec3& speed, float dampening);
    void setAngularSpeed(const glm::vec3& speed, float dampening);

    bool intersectionCheckDue() const;
    void intersectionCheckPerformed();

    void update(float deltaSec);

protected:
    WorldTransform m_transform;

    int m_color;
    float m_emissiveness;

    float m_lifetime;

    glm::vec3 m_directionalSpeed;
    float m_directionalDampening;

    glm::vec3 m_angularSpeed;
    float m_angularDampening;

    float m_intersectionCheckCountdown;
    bool m_intersectionChecked;

    static Property<float>* s_intersectionCheckPeriod;
};
