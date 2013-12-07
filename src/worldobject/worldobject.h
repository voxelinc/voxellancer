#pragma once

#include <list>
#include <memory>

#include "collision/collisiondetector.h"
#include "physics/physics.h"
#include "voxel/voxelcluster.h"
#include "ui/hudinfo.h"

class WorldObject : public VoxelCluster
{
public:
    WorldObject(float scale = 1.0f);
    virtual ~WorldObject();

    CollisionDetector& collisionDetector();
    Physics& physics();
    HUDInfo& hudInfo();

    AABB aabb();
    Sphere sphere();

    virtual void update(float delta_sec);

    std::list<Collision>& move(float delta_sec);

    void addVoxel(Voxel * voxel);
    void removeVoxel(const glm::ivec3 & position);
    void finishInitialization();

    Voxel *crucialVoxel();

    void accelerate(glm::vec3 direction);
    void accelerateAngular(glm::vec3 axis);

    void updateTransformAndGeode(const glm::vec3& position, const glm::quat& orientation);


protected:
    WorldObject(Physics* physics, CollisionDetector* detector, float scale = 1.0f);

    std::unique_ptr<CollisionDetector> m_collisionDetector;
    std::unique_ptr<Physics> m_physics;
    HUDInfo m_hudInfo;
};
