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

    float directionalDampening() const;
    void setDirectionalDampening(float directionalDampening);

    float angularDampening() const;
    void setAngularDampening(float angularDampening);

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

    float m_directionalDampening;
    float m_angularDampening;

    float m_mass;
    glm::vec3 m_accumulatedMassVec; // For fast recalc of center of mass on voxel addition/removal
    float m_massScaleFactor;

    std::list<VoxelCollision> m_collisions;

    void alterCell(Voxel* voxel, bool isAdd);
};

