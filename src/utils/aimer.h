#pragma once

#include <set>

#include "geometry/ray.h"

#include "property/property.h"


class Voxel;
class WorldObject;

/*
    Identifies the position of the voxel a worldObject is aiming at
*/
class Aimer {
public:
    Aimer(WorldObject* worldObject, const Ray& ray);

    glm::vec3 aim();


protected:
    WorldObject* m_worldObject;
    Ray m_ray;
    Property<float> m_infityAimDistance;

    glm::vec3 nearestTarget(const std::set<Voxel*>& voxels) const;
    float distanceTo(Voxel* voxel) const;
    glm::vec3 infinity() const ;
};

