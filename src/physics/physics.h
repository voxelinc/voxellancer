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

class Physics {
public:
    Physics(WorldObject& worldObject, float scale);

    float directionalDampening() const;
    void setDirectionalDampening(const Property<float>& directionalDampening);

    float angularDampening() const;
    void setAngularDampening(const Property<float>& directionalDampening);

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
    WorldObject& m_worldObject;
    Speed m_speed;
    Acceleration m_acceleration;

    Property<float> m_directionalDampening;
    Property<float> m_angularDampening;

    float m_mass;
    glm::vec3 m_accumulatedMassVec; // For fast recalc of center of mass on voxel addition/removal
    float m_massScaleFactor;

    void voxelChanged(Voxel* voxel, bool isAdd);
    virtual void updateSpeed(float deltaSec);
};

