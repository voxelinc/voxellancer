#pragma once

#include <list>
#include <memory>
#include <glm/glm.hpp>

#include "collision/voxelcollision.h"

#include "geometry/transform.h"
#include "geometry/speed.h"
#include "geometry/acceleration.h"

#include "property/property.h"

#include "physics/impulse.h"

#include "movement.h"


class WorldObject;
class Transform;

class Physics {
public:
    Physics(WorldObject& worldObject, float scale);

    const Acceleration& dampening() const;
    void setDampening(const Acceleration& dampening);

    const Speed& speed() const;
    void setSpeed(const Speed& speed);

    const Acceleration& acceleration() const;
    void setAcceleration(const Acceleration& acceleration);

    float mass() const;

    const Transform projectedTransformIn(float deltaSec);

    std::list<VoxelCollision>& move(float deltaSec);

    void addVoxel(Voxel* voxel);
    void removeVoxel(Voxel* voxel);


protected:
    virtual void updateSpeed(float deltaSec);


protected:
    WorldObject& m_worldObject;

    Speed m_speed;
    Acceleration m_acceleration;
    Acceleration m_dampening;

    float m_mass;
    std::list<VoxelCollision> m_collisions;
    glm::vec3 m_accumulatedMassVec;
    float m_massScaleFactor;

    void alterCell(Voxel* voxel, bool isAdd);
};

