#pragma once

#include <list>

#include "collision/collisiondetector.h"
#include "physics/physics.h"
#include "voxel/voxelcluster.h"

class WorldObject : public VoxelCluster
{
public:
    WorldObject(float scale = 1.0f);
    virtual ~WorldObject();

    CollisionDetector& collisionDetector();
    Physics& physics();

    AABB aabb();
    Sphere sphere();

    virtual void update(float delta_sec);

    std::list<Impact>& move(float delta_sec);

    void addVoxel(Voxel * voxel);
    void removeVoxel(const glm::ivec3 & position);
    void finishInitialization();

    Voxel *crucialVoxel();

    void accelerate(glm::vec3 direction);
    void accelerateAngular(glm::vec3 axis);

protected:
    CollisionDetector m_collisionDetector;
    Physics m_physics;
};
