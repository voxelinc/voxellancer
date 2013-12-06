#pragma once

#include <list>
#include <memory>
#include <glm/glm.hpp>

#include "collision/collision.h"
#include "property/property.h"
#include "worldtransform.h"
#include "world/helper/impact.h"

#include "movement.h"
#include "movephase.h"


class WorldObject;
class WorldTransform;

class Physics {
public:
    Physics(WorldObject& worldObject);
    virtual ~Physics();

    const glm::vec3& speed() const;
    void setSpeed(const glm::vec3& speed);

    const glm::vec3& angularSpeed() const;
    void setAngularSpeed(const glm::vec3& angularSpeed);

    const glm::vec3& acceleration() const;
    const glm::vec3& angularAcceleration() const;

    std::list<Collision>& move(float deltaSec);

    void accelerate(const glm::vec3& direction);
    void accelerateAngular(const glm::vec3& axis);

    void addVoxel(Voxel* voxel);
    void removeVoxel(const glm::ivec3& position);

    void finishInitialization();


protected:
    void calculateMassAndCenter();
    virtual void updateSpeed(float deltaSec);

    void applyTransform();
    void doSteppedTransform(const MovePhase& movePhase);
    void doWarpTransform(const MovePhase& movePhase);


protected:
    float m_mass;
    bool m_massValid;

    WorldObject& m_worldObject;

    glm::vec3 m_speed;
    glm::vec3 m_angularSpeed;

    glm::vec3 m_acceleration;
    glm::vec3 m_angularAcceleration;

    Movement m_movement;

    int m_steps;

    Property<float> m_dampening;
    Property<float> m_angularDampening;
    Property<float> m_rotationFactor;

   // std::list<Impact> m_impacts;
    std::list<Collision> m_collisions;
};

