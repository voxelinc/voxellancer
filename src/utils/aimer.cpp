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


Aimer::Aimer(WorldObject* worldObject) :
    m_worldObject(worldObject),
    m_infityAimDistance("general.infinityAimDistance"),
    m_infityAimInterpolation("general.infinityAimInterpolation"),
    m_lastDistance(0)
{
}

void Aimer::update(float deltaSec) {
    float interpolation = deltaSec * 0.3f;
    m_lastDistance = interpolation * m_infityAimDistance + (1 - interpolation) * m_lastDistance;
}

void Aimer::setWorldObject(WorldObject* worldObject) {
    m_worldObject = worldObject;
}

glm::vec3 Aimer::aim(const Ray& ray) {
    assert(m_worldObject);
    glm::vec3 targetPoint;

    WorldTreeQuery wordltreequery(&World::instance()->worldTree(), &ray, nullptr, &m_worldObject->collisionFilter());

    std::unordered_set<WorldObject*> intersectingWorldObjects = wordltreequery.intersectingWorldObjects();

    if(!intersectingWorldObjects.empty()) {
        targetPoint = nearestTarget(intersectingWorldObjects, ray);
    }
    
    m_lastDistance = glm::length(ray.origin() - targetPoint);
    return targetPoint;
}

glm::vec3 Aimer::nearestTarget(const std::unordered_set<WorldObject*>& worldObjects, const Ray& ray) const {
    WorldObject* nearest = nullptr;
    float minDistance = std::numeric_limits<float>::max();
    
    for(WorldObject* worldObject : worldObjects) {
        float distance = glm::length(worldObject->position() - ray.origin());
        if(distance < minDistance) {
            nearest = worldObject;
            minDistance = distance;
        }
    }

    glm::vec3 targetPoint = nearestVoxel(nearest, ray);
    
    return targetPoint;
}

glm::vec3 Aimer::nearestVoxel(WorldObject* object, const Ray& ray) const {
    VoxelTreeQuery voxelTreeQuery(object, &object->collisionDetector().voxelTree(), &ray);
    auto voxels = voxelTreeQuery.intersectingVoxels();

    Voxel* nearest = nullptr;
    float minDistance = std::numeric_limits<float>::max();


    for (Voxel* voxel : voxels) {
        float distance = distanceTo(voxel, object, ray.origin());
        if (distance < minDistance) {
            nearest = voxel;
            minDistance = distance;
        }
    }

    glm::vec3 targetPoint = nearest->position(object->transform());

    return targetPoint;
}


float Aimer::distanceTo(Voxel* voxel, WorldObject* owner, const glm::vec3& origin) const {
    return glm::length(voxel->position(owner->transform()) - origin);
}


