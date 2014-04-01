#pragma once

#include <list>
#include <memory>
#include <glm/glm.hpp>

#include "geometry/transform.h"
#include "geometry/speed.h"
#include "geometry/acceleration.h"

#include "property/property.h"


class WorldObject;
class Transform;
class Voxel;
class VoxelCollision;

/**
 * Component of the WorldObject that is managing
 *  - Movement (updating speed, performing the movement until collision)
 *  - The mass and center(that is shifted with added/removed Voxels) of the WorldObject
 */
class Physics {
public:
    Physics(WorldObject& worldObject);

    float directionalDampening() const;
    void setDirectionalDampening(const Property<float>& directionalDampening);

    float angularDampening() const;
    void setAngularDampening(const Property<float>& angularDampening);

    const Speed& speed() const;
    void setSpeed(const Speed& speed);

    const Acceleration& acceleration() const;
    void setAcceleration(const Acceleration& acceleration);

    float mass() const;
    float maxMass() const;

    const Transform projectedTransformIn(float deltaSec);

    std::list<VoxelCollision>& move(float deltaSec);

    void addVoxel(Voxel* voxel);
    void removeVoxel(Voxel* voxel);


protected:
    WorldObject& m_worldObject;
    Speed m_speed;
    Acceleration m_acceleration;

    Property<float> m_directionalDampening;
    Property<float> m_angularDampening;

    float m_unscaledMass;
    float m_maxUnscaledMass;
    glm::vec3 m_accumulatedUnscaledMassVec; // For fast recalc of center of mass on voxel addition/removal

    void voxelChanged(Voxel* voxel, bool isAdd);
    virtual void updateSpeed(float deltaSec);
};

