#include "aimer.h"

#include <limits>

#include <glm/glm.hpp>

#include "collision/collisiondetector.h"
#include "collision/collisionfilter.h"

#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "world/world.h"

#include "worldobject/worldobject.h"
#include "worldtree/worldtreequery.h"

#include "voxel/voxel.h"
#include "voxel/voxeltreequery.h"


Aimer::Aimer(WorldObject* worldObject, const Ray& ray):
    m_worldObject(worldObject),
    m_ray(ray),
    m_infityAimDistance("general.inifinityAimDistance")
{
}

glm::vec3 Aimer::aim() {
    glm::vec3 targetPoint;

    WorldTreeQuery wordltreequery(&World::instance()->worldTree(), &m_ray, nullptr, &m_worldObject->collisionFilter());

    std::unordered_set<WorldObject*> intersectingWorldObjects = wordltreequery.intersectingWorldObjects();

    if(!intersectingWorldObjects.empty()) {
        return nearestTarget(intersectingWorldObjects);
    }
    else {
        return infinity();
    }
}

glm::vec3 Aimer::nearestTarget(const std::unordered_set<WorldObject*>& worldObjects) const {
    WorldObject* nearest = nullptr;
    float minDistance = std::numeric_limits<float>::max();
    
    for(WorldObject* worldObject : worldObjects) {
        float distance = glm::length(worldObject->position() - m_ray.origin());
        if(distance < minDistance) {
            nearest = worldObject;
            minDistance = distance;
        }
    }

    glm::vec3 targetPoint = nearestVoxel(nearest);
    
    return targetPoint;
}

glm::vec3 Aimer::nearestVoxel(WorldObject* object) const {
    VoxelTreeQuery voxelTreeQuery(object, &object->collisionDetector().voxelTree(), &m_ray);
    auto voxels = voxelTreeQuery.intersectingVoxels();

    Voxel* nearest = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (Voxel* voxel : voxels) {
        float distance = distanceTo(voxel, object);
        if (distance < minDistance) {
            nearest = voxel;
            minDistance = distance;
        }
    }

    glm::vec3 targetPoint = nearest->position(object->transform());

    return targetPoint;
}


float Aimer::distanceTo(Voxel* voxel, WorldObject* owner) const {
    return glm::length(voxel->position(owner->transform()) - m_ray.origin());
}

glm::vec3 Aimer::infinity() const {
    return m_ray.origin() + m_ray.direction() * m_infityAimDistance.get();
}

