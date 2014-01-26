#include "aimer.h"

#include <glm/glm.hpp>

#include "collision/collisionfilterable.h"

#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "world/world.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreequery.h"


namespace {
    class CollisionFilter: public CollisionFilterable {
    public:
        CollisionFilter(WorldObject* worldObject):
            CollisionFilterable(CollisionFilterClass::Other),
            m_worldObject(worldObject)
        {
        }

        virtual bool specialIsCollideableWith(const CollisionFilterable *other) const override {
            return m_worldObject != other;
        }


    protected:
        WorldObject* m_worldObject;
    };
}

Aimer::Aimer(WorldObject* worldObject, const Ray& ray):
    m_worldObject(worldObject),
    m_ray(ray)
{
}

glm::vec3 Aimer::aim() {
    glm::vec3 targetPoint;

    CollisionFilter collisionFilter(m_worldObject);
    WorldTreeQuery wordltreequery(&World::instance()->worldTree(), &m_ray, nullptr, &collisionFilter);

    std::set<Voxel*> intersectingVoxels = wordltreequery.intersectingVoxels();

    if(!intersectingVoxels.empty()) {
        return nearestTarget(intersectingVoxels);
    }
    else {
        return infinity();
    }
}

glm::vec3 Aimer::nearestTarget(const std::set<Voxel*>& voxels) const {
    Voxel* anyVoxel = *voxels.begin();

    float minDistance = distanceTo(anyVoxel);
    glm::vec3 targetPoint = anyVoxel->position();

    for(Voxel* voxel : voxels) {
        float distance = distanceTo(voxel);

        if(distance < minDistance) {
            targetPoint = voxel->position();
            minDistance = distance;
        }
    }

    return targetPoint;
}

float Aimer::distanceTo(Voxel* voxel) const {
    return glm::length(voxel->position() - m_ray.origin());
}

glm::vec3 Aimer::infinity() const {
    return m_ray.origin() + m_ray.direction() * 512.0f;
}

