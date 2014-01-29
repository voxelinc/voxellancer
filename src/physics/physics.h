#pragma once

#include <list>
#include <memory>
#include <glm/glm.hpp>

#include "collision/voxelcollision.h"
#include "property/property.h"
#include "geometry/transform.h"
#include "physics/impulse.h"

#include "movement.h"


class WorldObject;
class Transform;

class Physics {
public:
    Physics(WorldObject& worldObject, float scale);
    virtual ~Physics();

    float directionalDampening();
    void setDirectionalDampening(float dampening);

    float angularDampening();
    void setAngularDampening(float angularDampening);

    const glm::vec3& directionalSpeed() const;
    void setDirectionalSpeed(const glm::vec3& speed);

    const glm::vec3& angularSpeed() const;
    void setAngularSpeed(const glm::vec3& angularSpeed);

    void accelerateDirectional(const glm::vec3& direction);
    const glm::vec3& directionalAcceleration() const;

    void accelerateAngular(const glm::vec3& axis);
    const glm::vec3& angularAcceleration() const;

    float mass() const;

    const Transform projectedTransformIn(float deltaSec);

    std::list<VoxelCollision>& move(float deltaSec);

    void addVoxel(Voxel* voxel);
    void removeVoxel(Voxel* voxel);


protected:
    virtual void updateSpeed(float deltaSec);


protected:
    WorldObject& m_worldObject;

    glm::vec3 m_directionalSpeed;
    glm::vec3 m_angularSpeed;

    glm::vec3 m_directionalAcceleration;
    glm::vec3 m_angularAcceleration;

    float m_directionalDampening;
    float m_angularDampening;

    float m_mass;
    std::list<VoxelCollision> m_collisions;
    glm::vec3 m_accumulatedMassVec;
    float m_massScaleFactor;

    void alterCell(Voxel* voxel, bool isAdd);
};

