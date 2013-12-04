#pragma once

#include <list>
#include <memory>
#include <glm/glm.hpp>

#include "collision/collision.h"
#include "property/property.h"
#include "worldtransform.h"
#include "world/helper/impact.h"

class WorldObject;
class WorldTransform;

class Physics  {
public:
    Physics(WorldObject & worldObject);
    virtual ~Physics();

    const glm::vec3& speed() const;
    void setSpeed(const glm::vec3& speed);

    const glm::vec3& angularSpeed() const;
    void setAngularSpeed(const glm::vec3& angularSpeed);

    const glm::vec3& acceleration() const;
    const glm::vec3& angularAcceleration() const;

    std::list<Impact> &move(float delta_sec);

    void accelerate(glm::vec3 direction);
    void accelerateAngular(glm::vec3 axis);

    void addVoxel(Voxel *voxel);
    void removeVoxel(const glm::ivec3 &position);

    void finishInitialization();

protected:
    void calculateMassAndCenter();

    void resolveCollision(Collision & c, float delta_sec);
    void applyTransform();
    void doSteppedTransform();
    float calculateStepCount(const WorldTransform & oldTransform, const WorldTransform & newTransform);
    bool isCollisionPossible();

protected:
    float m_mass;
    bool m_massValid;

    WorldObject& m_worldObject;

    WorldTransform m_oldTransform;
    WorldTransform m_newTransform;

    glm::vec3 m_speed;
    glm::vec3 m_angularSpeed;

    glm::vec3 m_acceleration;
    glm::vec3 m_angularAcceleration;

    Property<float> m_dampening;
    Property<float> m_angularDampening;
    Property<float> m_rotationFactor;

    std::list<Impact> m_impacts;
};
