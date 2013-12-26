#pragma once

#include <list>
#include <memory>
#include <glm/glm.hpp>

#include "collision/voxelcollision.h"
#include "property/property.h"
#include "worldtransform.h"
#include "physics/impulse.h"

#include "movement.h"


class WorldObject;
class WorldTransform;

class Physics {
public:
    Physics(WorldObject& worldObject, float scale);
    virtual ~Physics();

    const glm::vec3& speed() const;
    void setSpeed(const glm::vec3& speed);

    const glm::vec3& angularSpeed() const;
    void setAngularSpeed(const glm::vec3& angularSpeed);

    const glm::vec3& acceleration() const;
    const glm::vec3& angularAcceleration() const;

    float mass() const;

    std::list<VoxelCollision>& move(float deltaSec);

    void accelerate(const glm::vec3& direction);
    void accelerateAngular(const glm::vec3& axis);

    void addVoxel(Voxel* voxel);
    void removeVoxel(Voxel* voxel);


protected:
    virtual void updateSpeed(float deltaSec);


protected:
    WorldObject& m_worldObject;

    glm::vec3 m_speed;
    glm::vec3 m_angularSpeed;

    glm::vec3 m_acceleration;
    glm::vec3 m_angularAcceleration;

    Property<float> m_dampening;
    Property<float> m_angularDampening;

    float m_mass;
    std::list<VoxelCollision> m_collisions;
    glm::vec3 m_accumulatedMassVec;
    float m_massScaleFactor;

    void alterCell(Voxel* voxel, bool isAdd);
};

