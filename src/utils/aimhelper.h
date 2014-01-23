#pragma once

#include <set>

#include "geometry/ray.h"


class Voxel;
class WorldObject;

class AimHelper {
public:
    AimHelper(WorldObject* worldObject, const Ray& ray);

    glm::vec3 aim();


protected:
    WorldObject* m_worldObject;
    Ray m_ray;

    glm::vec3 nearestTarget(const std::set<Voxel*>& voxels) const;
    float distanceTo(Voxel* voxel) const;
    glm::vec3 infinity() const ;
};

