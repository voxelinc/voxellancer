#include "aimer.h"

#include <glm/glm.hpp>

#include "collision/collisiondetector.h"
#include "collision/collisionfilter.h"

#include "voxel/voxel.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "world/world.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreegeode.h"
#include "worldtree/worldtreequery.h"


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
    assert(m_worldObject->collisionDetector().geode());

    glm::vec3 targetPoint;

    WorldTreeQuery query(&World::instance()->worldTree(), &ray, m_worldObject->collisionDetector().geode()->hint(), &m_worldObject->collisionFilter());

    std::unordered_set<Voxel*> intersectingVoxels = query.intersectingVoxels();

    if(!intersectingVoxels.empty()) {
        targetPoint = nearestTarget(intersectingVoxels, ray.origin());
    } else {
        targetPoint = infinity(ray);
    }

    m_lastDistance = glm::length(ray.origin() - targetPoint);
    return targetPoint;
}

glm::vec3 Aimer::nearestTarget(const std::unordered_set<Voxel*>& voxels, const glm::vec3& origin) const {
    Voxel* anyVoxel = *voxels.begin();

    float minDistance = distanceTo(anyVoxel, origin);
    glm::vec3 targetPoint = anyVoxel->position();

    for(Voxel* voxel : voxels) {
        float distance = distanceTo(voxel, origin);

        if(distance < minDistance) {
            targetPoint = voxel->position();
            minDistance = distance;
        }
    }

    return targetPoint;
}

float Aimer::distanceTo(Voxel* voxel, const glm::vec3& origin) const {
    return glm::length(voxel->position() - origin);
}

glm::vec3 Aimer::infinity(const Ray& ray) const {
    return ray.origin() + ray.direction() * m_lastDistance;
}

