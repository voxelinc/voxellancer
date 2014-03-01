#pragma once

#include <unordered_set>

#include "geometry/ray.h"

#include "property/property.h"


class Voxel;
class WorldObject;

/*
    Identifies the position of the voxel a worldObject is aiming at
*/
class Aimer {
public:
    Aimer(WorldObject* worldObject);
    void update(float deltaSec);

    glm::vec3 aim(const Ray& ray);

    void setWorldObject(WorldObject* worldObject);
    
protected:
    WorldObject* m_worldObject;
    Property<float> m_infityAimDistance;
    Property<float> m_infityAimInterpolation;
    float m_lastDistance;

    glm::vec3 nearestTarget(const std::unordered_set<WorldObject*>& voxels, const Ray& ray) const;
    glm::vec3 nearestVoxel(WorldObject* nearest, const Ray& ray) const;

    float distanceTo(Voxel* voxel, WorldObject* owner, const glm::vec3& origin) const;
    glm::vec3 infinity(const Ray& ray) const;

};

